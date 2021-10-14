#include <assert.h>
#include <stdbool.h>

#include "3rd_party/map/map.h"
#include "3rd_party/parson/parson.h"
#include "3rd_party/stb/stb_image_write.h"
#include "3rd_party/stb/stb_truetype.h"
#include "3rd_party/vec/vec.h"
#include "mcore/mcommon.h"
#include "mcore/mdata.h"
#include "mcore/mfile.h"
#include "mcore/mimport.h"
#include "mcore/mlog.h"
#include "mcore/mstring.h"
#include "golf/data_stream.h"
#include "golf/log.h"

typedef struct _mimporter {
    const char *ext;
    void (*callback)(mdatafile_t *file, void *udata);
    void *udata;
} _mimporter_t;

#define _VAL_MAX_NAME_LEN 32

enum _val_type {
    _VAL_TYPE_INT,
    _VAL_TYPE_STRING,
    _VAL_TYPE_DATA,
};

typedef struct _val {
    enum _val_type type;
    union {
        int int_val;
        struct {
            unsigned char *data_val;
            int data_val_len;
        };
        char *string_val;
    };
    char name[_VAL_MAX_NAME_LEN];
    bool user_set;
} _val_t;

typedef vec_t(_val_t) _vec_val_t;

typedef struct mdatafile {
    char name[1024];
    char path[1024];
    _vec_val_t vals_vec;
    bool has_cached_vals;
    _vec_val_t cached_vals_vec;
    mfiletime_t filetime;

    JSON_Value *json_val;
} mdatafile_t;

typedef map_t(_mimporter_t) _map_mimporter_t;
static _map_mimporter_t _importers_map;
static mdir_t _data_dir;

static void _create_texture_mdatafile(mfile_t *file, mdatafile_t *mdatafile) {
    mdatafile_add_string(mdatafile, "filter", "linear", true);
    mdatafile_add_data(mdatafile, "data", file->data, file->data_len);
}

static void _shader_mdatafile_add_bare_shaders(mdatafile_t *file, const char *base_name, const char *fs_name, const char *vs_name, const char *ext) {
	mstring_t fs_bare_name;
	mstring_initf(&fs_bare_name, "%s_%s.%s", base_name, fs_name, ext);
	unsigned char *fs_data;
	int fs_data_len;
	if (!mread_file(fs_bare_name.cstr, &fs_data, &fs_data_len)) {
		mlog_error("Failed to read file %s", fs_bare_name.cstr);
	}
	mdatafile_add_data(file, fs_name, fs_data, fs_data_len);
	free(fs_data);
	mstring_deinit(&fs_bare_name);

	mstring_t vs_bare_name;
	mstring_initf(&vs_bare_name, "%s_%s.%s", base_name, vs_name, ext);
	unsigned char *vs_data;
	int vs_data_len;
	if (!mread_file(vs_bare_name.cstr, &vs_data, &vs_data_len)) {
		mlog_error("Failed to read file %s", vs_bare_name.cstr);
	}
	mdatafile_add_data(file, vs_name, vs_data, vs_data_len);
	free(vs_data);
	mstring_deinit(&vs_bare_name);
}

static void _create_shader_mdatafile(mfile_t *file, mdatafile_t *mdatafile) {
    const char *slangs = "glsl330:glsl300es";
	int ret;
	mstring_t cmd;
	//mstring_initf(&cmd, "tools\\sokol-tools\\win32\\sokol-shdc.exe --input %s --output src/golf/shaders/%s.h --slang glsl330:glsl300es:metal_macos:metal_ios:metal_sim", file_path, file_name);
	//mstring_initf(&cmd, "tools/sokol-tools/osx/sokol-shdc --input %s --output src/golf/shaders/%s.h --slang glsl330:glsl300es:metal_macos:metal_ios:metal_sim", file_path, file_name);
	mstring_initf(&cmd, "tools/sokol-tools/linux/sokol-shdc --input %s --output src/golf2/shaders/%s.h --slang %s", file->path, file->name, slangs);
	ret = system(cmd.cstr);
	mstring_deinit(&cmd);

	//mstring_initf(&cmd, "tools\\sokol-tools\\win32\\sokol-shdc.exe --input %s --output out/temp/bare --slang glsl330:glsl300es:metal_macos:metal_ios:metal_sim --format bare", file_path, file_name);
	//mstring_initf(&cmd, "tools/sokol-tools/osx/sokol-shdc --input %s --output out/temp/bare --slang glsl330:glsl300es:metal_macos:metal_ios:metal_sim --format bare", file_path, file_name);
	mstring_initf(&cmd, "tools/sokol-tools/linux/sokol-shdc --input %s --output out/temp/bare --slang %s --format bare", file->path, slangs);
	ret = system(cmd.cstr);
	if (ret == 0) {
		mstring_t base_bare_name;
		mstring_initf(&base_bare_name, "out/temp/bare_%s", file->name);
		mstring_pop(&base_bare_name, 5);

		_shader_mdatafile_add_bare_shaders(mdatafile, base_bare_name.cstr, "glsl300es_fs", "glsl300es_vs", "glsl");
		_shader_mdatafile_add_bare_shaders(mdatafile, base_bare_name.cstr, "glsl330_fs", "glsl330_vs", "glsl");

		mstring_deinit(&base_bare_name);
	}
	mstring_deinit(&cmd);
}

void _stbi_write_func(void *context, void *data, int size) {
    vec_char_t *bmp = (vec_char_t*)context;
    vec_pusharr(bmp, (char*)data, size);
}

static void _font_mdatafile_add_size(mfile_t *file, mdatafile_t *mdatafile, 
        const char *size_name, int font_size, int bitmap_size) {
    unsigned char *bitmap = malloc(bitmap_size * bitmap_size);
    stbtt_bakedchar cdata[96];
    stbtt_BakeFontBitmap(file->data, 0, -font_size, bitmap, bitmap_size, bitmap_size, 32, 95, cdata);

    float ascent, descent, linegap;
    stbtt_GetScaledFontVMetrics(file->data, 0, -font_size, &ascent, &descent, &linegap);
    {
        mstring_t ascent_name;
        mstring_initf(&ascent_name, "%s_ascent", size_name);
        mdatafile_add_int(mdatafile, ascent_name.cstr, (int)ascent, false);
        mstring_deinit(&ascent_name);
    }

    {
        mstring_t descent_name;
        mstring_initf(&descent_name, "%s_descent", size_name);
        mdatafile_add_int(mdatafile, descent_name.cstr, (int)descent, false);
        mstring_deinit(&descent_name);
    }

    {
        mstring_t linegap_name;
        mstring_initf(&linegap_name, "%s_linegap", size_name);
        mdatafile_add_int(mdatafile, linegap_name.cstr, (int)linegap, false);
        mstring_deinit(&linegap_name);
    }

    {
        mstring_t bitmap_size_name;
        mstring_initf(&bitmap_size_name, "%s_bitmap_size", size_name);
        mdatafile_add_int(mdatafile, bitmap_size_name.cstr, bitmap_size, false);
        mstring_deinit(&bitmap_size_name);
    }

    {
        mstring_t font_size_name;
        mstring_initf(&font_size_name, "%s_font_size", size_name);
        mdatafile_add_int(mdatafile, font_size_name.cstr, font_size, false);
        mstring_deinit(&font_size_name);
    }

    {
        vec_char_t bmp;
        vec_init(&bmp);
        stbi_write_bmp_to_func(_stbi_write_func, &bmp, bitmap_size, bitmap_size, 1, bitmap);
        mstring_t bitmap_data_name;
        mstring_initf(&bitmap_data_name, "%s_bitmap_data", size_name);
        mdatafile_add_data(mdatafile, bitmap_data_name.cstr, bmp.data, bmp.length);
        mstring_deinit(&bitmap_data_name);
        vec_deinit(&bmp);
    }

    {
        mstring_t str;
        mstring_init(&str, "[");
        for (int i = 32; i < 126; i++) {
            stbtt_bakedchar c = cdata[i - 32];
            mstring_appendf(&str, "[%d, %d, %d, %d, %d, %.3f, %.3f, %.3f]", i, c.x0, c.y0, c.x1, c.y1, c.xoff, c.yoff, c.xadvance);
            if (i < 125) {
                mstring_append_cstr(&str, ", ");
            }
        }
        mstring_append_cstr(&str, "]");
        mstring_t char_data_name;
        mstring_initf(&char_data_name, "%s_char_data", size_name);
        mdatafile_add_data(mdatafile, char_data_name.cstr, str.cstr, str.len);
        mstring_deinit(&char_data_name);
        mstring_deinit(&str);
    }

    free(bitmap);
}

static void _create_font_mdatafile(mfile_t *file, mdatafile_t *mdatafile) {
    _font_mdatafile_add_size(file, mdatafile, "small", 16, 128);
    _font_mdatafile_add_size(file, mdatafile, "medium", 32, 256);
    _font_mdatafile_add_size(file, mdatafile, "large", 64, 512);
}

static void _create_default_mdatafile(mfile_t *file, mdatafile_t *mdatafile) {
    mdatafile_add_data(mdatafile, "data", file->data, file->data_len);
}

void mimport_init(int num_embedded_files, membedded_file_t *embedded_files) {
    map_init(&_importers_map);
    mdir_init(&_data_dir, "data", true);
    mimport_run();
}

void mimport_add_importer(const char *ext, void (*callback)(mdatafile_t *file, void *udata), void *udata) {
    _mimporter_t importer;
    importer.ext = ext;
    importer.callback = callback;
    importer.udata = udata;
    map_set(&_importers_map, ext, importer);
    for (int i = 0; i < _data_dir.num_files; i++) {
        mfile_t file = _data_dir.files[i];
        if (strcmp(file.ext, ext) != 0) {
            continue;
        }

        mdatafile_t *mdatafile = mdatafile_load(file.path);
        callback(mdatafile, udata);
        mdatafile_delete(mdatafile);
    }
}

void mimport_run(void) {
    int num_files_imported = 0;

    for (int i = 0; i < _data_dir.num_files; i++) {
        mfile_t file = _data_dir.files[i];
        if ((strcmp(file.ext, ".mdata") == 0) ||
                (strcmp(file.ext, ".mdata_texture") == 0) ||
                (strcmp(file.ext, ".mdata_shader") == 0) ||
                (strcmp(file.ext, ".mdata_config") == 0) ||
                (strcmp(file.ext, ".mdata_model") == 0) ||
                (strcmp(file.ext, ".mdata_font") == 0)) {
            continue;
        }

        // Check if we need to update the .mdata file
        mfiletime_t file_time;
        mfile_get_time(&file, &file_time);

        char mdatafile_path[1030];
        snprintf(mdatafile_path, 1030, "%s.mdata", file.path);
        mfile_t mdatafile_file = mfile(mdatafile_path);
        mfiletime_t mdatafile_file_time;
        mfile_get_time(&mdatafile_file, &mdatafile_file_time);

        //if (mfiletime_cmp(file_time, mdatafile_file_time) < 0) {
        //continue;
        //}

        num_files_imported++;
        mlog_note("Importing %s", file.path);
        if (!mfile_load_data(&file)) {
            mlog_error("Could not load file %s", file.path);
        }

        mdatafile_t *mdatafile = mdatafile_load(file.path);
        mdatafile_cache_old_vals(mdatafile);

        if ((strcmp(file.ext, ".png") == 0) ||
                (strcmp(file.ext, ".bmp") == 0) || 
                (strcmp(file.ext, ".jpg") == 0)) {
            mdata_texture_import(&file);
            _create_texture_mdatafile(&file, mdatafile);
        }
        else if ((strcmp(file.ext, ".glsl") == 0)) {
            mdata_shader_import(&file);
            _create_shader_mdatafile(&file, mdatafile);
        }
        else if ((strcmp(file.ext, ".ttf") == 0)) {
            mdata_font_import(&file);
            _create_font_mdatafile(&file, mdatafile);
        }
        else if((strcmp(file.ext, ".obj") == 0)) {
            mdata_model_import(&file);
            _create_default_mdatafile(&file, mdatafile);
        }
        else if ((strcmp(file.ext, ".cfg") == 0) ||
                (strcmp(file.ext, ".mscript") == 0) ||
                (strcmp(file.ext, ".ogg") == 0) ||
                (strcmp(file.ext, ".fnt") == 0) ||
                (strcmp(file.ext, ".terrain_model") == 0) ||
                (strcmp(file.ext, ".hole") == 0) ||
                (strcmp(file.ext, ".model") == 0) ||
                (strcmp(file.ext, ".ui_menu") == 0) ||
                (strcmp(file.ext, ".obj") == 0)) {
            _create_default_mdatafile(&file, mdatafile);
        }
        else {
            mlog_warning("Unknown file type in data folder %s", file.ext); 
        }

        _mimporter_t *importer = map_get(&_importers_map, file.ext);
        if (importer) {
            importer->callback(mdatafile, importer->udata);
        }

        mdatafile_save(mdatafile);
        mdatafile_delete(mdatafile);
        mfile_free_data(&file);
    }
}

static _val_t _create_int_val(const char *name, int int_val) {
    _val_t val;
    val.type = _VAL_TYPE_INT;
    mstrncpy(val.name, name, _VAL_MAX_NAME_LEN);
    val.int_val = int_val;
    return val;
}

static _val_t _create_string_val(const char *name, const char *string_val) {
    _val_t val;
    val.type = _VAL_TYPE_STRING;
    mstrncpy(val.name, name, _VAL_MAX_NAME_LEN);
    int n = (int) strlen(string_val) + 1;
    val.string_val = malloc(sizeof(char) * n);
    mstrncpy(val.string_val, string_val, n);
    return val;
}

static _val_t _create_data_val(const char *name, const unsigned char *data, int data_len) {
    _val_t val;
    val.type = _VAL_TYPE_DATA;
    mstrncpy(val.name, name, _VAL_MAX_NAME_LEN);
    val.data_val = malloc(data_len + 1);
    memcpy(val.data_val, data, data_len);
    val.data_val[data_len] = 0;
    val.data_val_len = data_len;
    return val;
}

mdatafile_t *mdatafile_load(const char *path) {
    mdatafile_t *mdatafile = malloc(sizeof(mdatafile_t));
    vec_init(&mdatafile->vals_vec);
    mdatafile->has_cached_vals = false;

    snprintf(mdatafile->name, 1024, "%s", path);
    snprintf(mdatafile->path, 1024, "%s.mdata", path);
    unsigned char *data = NULL;
    int data_len = 0;

    if (!mread_file(mdatafile->path, &data, &data_len)) {
        return mdatafile;
    }

    if (!data) {
        mlog_error("Unable to load data for mdatafile %s", mdatafile->path);
    }

    {
        mfile_t file = mfile(mdatafile->path);
        mfile_get_time(&file, &mdatafile->filetime);
    }

    int i = 0;
    while (i < data_len) {
        int type_len = 0;
        char type[32]; 

        int name_len = 0;
        char name[_VAL_MAX_NAME_LEN + 1];

        while (data[i] != ' ') {
            if (i >= data_len) assert(false);
            type[type_len++] = data[i++];
            if (type_len >= 32) {
                assert(false);
            }
        }
        type[type_len] = 0;

        if (i >= data_len) assert(false);
        i++;

        while (data[i] != ' ') {
            if (i >= data_len) assert(false);
            name[name_len++] = data[i++];
            if (name_len >= _VAL_MAX_NAME_LEN + 1) {
                assert(false);
            }
        }
        name[name_len] = 0;

        if (i >= data_len) assert(false);
        i++;

        _val_t val;
        memset(&val, 0, sizeof(val));
        if (strcmp(type, "int") == 0) {
            int int_val = 0;
            bool is_neg = false;
            if (data[i] == '-') {
                is_neg = true;
                i++;
            }
            while (data[i] != '\n') {
                if (data[i] < '0' || data[i] > '9') {
                    assert(false);
                }

                int_val *= 10;
                int_val += data[i++] - '0';
            }
            i++;

            if (is_neg) {
                int_val *= -1;
            }
            mdatafile_add_int(mdatafile, name, int_val, false);
        }
        else if (strcmp(type, "string") == 0) {
            mstring_t str;
            mstring_init(&str, "");
            while (data[i] != '\n') {
                mstring_append_char(&str, data[i++]);
            }
            i++;

            mdatafile_add_string(mdatafile, name, str.cstr, false);
            mstring_deinit(&str);
        }
        else if (strcmp(type, "data") == 0) {
            mstring_t str;
            mstring_init(&str, "");
            while (data[i] != '\n') {
                mstring_append_char(&str, data[i++]);
            }
            i++;

            int data_len;
            unsigned char *data = mbase64_decode(str.cstr, str.len, &data_len); 
            mdatafile_add_data(mdatafile, name, data, data_len);
            free(data);
            mstring_deinit(&str);
        }
        else {
            mlog_error("Failed loading mdatafile %s. Unknown type %s.", mdatafile->path, type);
        }
    }

    free(data);
    return mdatafile;
}

static void _delete_vals_vec(_vec_val_t *vec) {
    for (int i = 0; i < vec->length; i++) {
        switch (vec->data[i].type) {
            case _VAL_TYPE_INT:
                break;
            case _VAL_TYPE_STRING:
                free(vec->data[i].string_val);
                break;
            case _VAL_TYPE_DATA:
                free(vec->data[i].data_val);
                break;
        }
    }
    vec_deinit(vec);
}

void mdatafile_delete(mdatafile_t *file) {
    _delete_vals_vec(&file->vals_vec);
    if (file->has_cached_vals) {
        _delete_vals_vec(&file->cached_vals_vec);
    }
    free(file);
}

void mdatafile_save(mdatafile_t *file) {
    mstring_t str;
    mstring_init(&str, "");
    for (int i = 0; i < file->vals_vec.length; i++) {
        _val_t val = file->vals_vec.data[i];
        switch (val.type) {
            case _VAL_TYPE_INT:
                mstring_appendf(&str, "int %s %d\n", val.name, val.int_val);
                break;
            case _VAL_TYPE_STRING:
                mstring_appendf(&str, "string %s %s\n", val.name, val.string_val);
                break;
            case _VAL_TYPE_DATA:
                {
                    char *enc = mbase64_encode(val.data_val, val.data_val_len);
                    mstring_appendf(&str, "data %s %s\n", val.name, enc);
                    free(enc);
                }
                break;
        }
    }
    mwrite_file(file->path, (unsigned char*) str.cstr, str.len);
    mstring_deinit(&str);
}

void mdatafile_cache_old_vals(mdatafile_t *file) {
    if (file->has_cached_vals) {
        _delete_vals_vec(&file->cached_vals_vec);
    }

    file->has_cached_vals = true;
    file->cached_vals_vec = file->vals_vec; 
    vec_init(&file->vals_vec);
}

static bool _find_cached_val(mdatafile_t *file, const char *name, enum _val_type type, _val_t *val) {
    if (!file->has_cached_vals) {
        return false;
    }

    for (int i = 0; i < file->cached_vals_vec.length; i++) {
        if (type == file->cached_vals_vec.data[i].type 
                && strcmp(file->cached_vals_vec.data[i].name, name) == 0) {
            *val = file->cached_vals_vec.data[i];
            return true;
        }
    }
    return false;
}

static bool _find_val(_vec_val_t *vals_vec, const char *name, enum _val_type type, _val_t *val) {
    for (int i = 0; i < vals_vec->length; i++) {
        if (type == vals_vec->data[i].type 
                && strcmp(vals_vec->data[i].name, name) == 0) {
            *val = vals_vec->data[i];
            return true;
        }
    }
    return false;
}

void mdatafile_add_int(mdatafile_t *file, const char *name, int int_val, bool user_set) {
    _val_t val, cached_val;
    if (user_set && _find_cached_val(file, name, _VAL_TYPE_INT, &cached_val)) {
        val = _create_int_val(name, cached_val.int_val);
    }
    else {
        val = _create_int_val(name, int_val);
    }
    vec_push(&file->vals_vec, val);
}

void mdatafile_add_string(mdatafile_t *file, const char *name, const char *string, bool user_set) {
    _val_t val, cached_val;
    if (user_set && _find_cached_val(file, name, _VAL_TYPE_STRING, &cached_val)) {
        val = _create_string_val(name, cached_val.string_val);
    }
    else {
        val = _create_string_val(name, string);
    }
    vec_push(&file->vals_vec, val);
}

void mdatafile_add_data(mdatafile_t *file, const char *name, unsigned char *data, int data_len) {
    _val_t val = _create_data_val(name, data, data_len);
    vec_push(&file->vals_vec, val);
}

const char *mdatafile_get_name(mdatafile_t *file) {
    return file->name;
}

bool mdatafile_get_int(mdatafile_t *file, const char *name, int *int_val) {
    _val_t val;
    if (_find_val(&file->vals_vec, name, _VAL_TYPE_INT, &val)) {
        *int_val = val.int_val;
        return true;
    }
    else {
        *int_val = 0;
        return false;
    }
}

bool mdatafile_get_string(mdatafile_t *file, const char *name, const char **string) {
    _val_t val;
    if (_find_val(&file->vals_vec, name, _VAL_TYPE_STRING, &val)) {
        *string = val.string_val;
        return true;
    }
    else {
        *string = NULL;
        return false;
    }
}

bool mdatafile_get_data(mdatafile_t *file, const char *name, unsigned char **data, int *data_len) {
    _val_t val;
    if (_find_val(&file->vals_vec, name, _VAL_TYPE_DATA, &val)) {
        *data = val.data_val;
        *data_len = val.data_val_len;
        return true;
    }
    else {
        *data = NULL;
        *data_len = 0;
        return false;
    }
}

mfiletime_t mdatafile_get_filetime(mdatafile_t *file) {
    return file->filetime;
}
