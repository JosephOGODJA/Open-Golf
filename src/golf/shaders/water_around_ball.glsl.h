#pragma once
/*
    #version:1# (machine generated, don't edit!)

    Generated by sokol-shdc (https://github.com/floooh/sokol-tools)

    Cmdline: sokol-shdc --input data/shaders/water_around_ball.glsl --output src/golf/shaders/water_around_ball.glsl.h --slang glsl330:glsl300es

    Overview:

        Shader program 'water_around_ball':
            Get shader desc: water_around_ball_shader_desc(sg_query_backend());
            Vertex shader: water_around_ball_vs
                Attribute slots:
                    ATTR_water_around_ball_vs_position = 0
                    ATTR_water_around_ball_vs_texture_coord = 1
                Uniform block 'water_around_ball_vs_params':
                    C struct: water_around_ball_vs_params_t
                    Bind slot: SLOT_water_around_ball_vs_params = 0
            Fragment shader: water_around_ball_fs
                Uniform block 'water_around_ball_fs_params':
                    C struct: water_around_ball_fs_params_t
                    Bind slot: SLOT_water_around_ball_fs_params = 0
                Image 'water_around_ball_noise_tex':
                    Type: SG_IMAGETYPE_2D
                    Component Type: SG_SAMPLERTYPE_FLOAT
                    Bind slot: SLOT_water_around_ball_noise_tex = 0


    Shader descriptor structs:

        sg_shader water_around_ball = sg_make_shader(water_around_ball_shader_desc(sg_query_backend()));

    Vertex attribute locations for vertex shader 'water_around_ball_vs':

        sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc){
            .layout = {
                .attrs = {
                    [ATTR_water_around_ball_vs_position] = { ... },
                    [ATTR_water_around_ball_vs_texture_coord] = { ... },
                },
            },
            ...});

    Image bind slots, use as index in sg_bindings.vs_images[] or .fs_images[]

        SLOT_water_around_ball_noise_tex = 0;

    Bind slot and C-struct for uniform block 'water_around_ball_vs_params':

        water_around_ball_vs_params_t water_around_ball_vs_params = {
            .mvp_mat = ...;
        };
        sg_apply_uniforms(SG_SHADERSTAGE_[VS|FS], SLOT_water_around_ball_vs_params, &SG_RANGE(water_around_ball_vs_params));

    Bind slot and C-struct for uniform block 'water_around_ball_fs_params':

        water_around_ball_fs_params_t water_around_ball_fs_params = {
            .t = ...;
        };
        sg_apply_uniforms(SG_SHADERSTAGE_[VS|FS], SLOT_water_around_ball_fs_params, &SG_RANGE(water_around_ball_fs_params));

*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#if !defined(SOKOL_SHDC_ALIGN)
  #if defined(_MSC_VER)
    #define SOKOL_SHDC_ALIGN(a) __declspec(align(a))
  #else
    #define SOKOL_SHDC_ALIGN(a) __attribute__((aligned(a)))
  #endif
#endif
#define ATTR_water_around_ball_vs_position (0)
#define ATTR_water_around_ball_vs_texture_coord (1)
#define SLOT_water_around_ball_noise_tex (0)
#define SLOT_water_around_ball_vs_params (0)
#pragma pack(push,1)
SOKOL_SHDC_ALIGN(16) typedef struct water_around_ball_vs_params_t {
    mat4 mvp_mat;
} water_around_ball_vs_params_t;
#pragma pack(pop)
#define SLOT_water_around_ball_fs_params (0)
#pragma pack(push,1)
SOKOL_SHDC_ALIGN(16) typedef struct water_around_ball_fs_params_t {
    float t;
    uint8_t _pad_4[12];
} water_around_ball_fs_params_t;
#pragma pack(pop)
/*
    #version 330
    
    uniform vec4 water_around_ball_vs_params[4];
    out vec2 frag_texture_coord;
    layout(location = 1) in vec2 texture_coord;
    layout(location = 0) in vec3 position;
    
    void main()
    {
        frag_texture_coord = texture_coord;
        gl_Position = mat4(water_around_ball_vs_params[0], water_around_ball_vs_params[1], water_around_ball_vs_params[2], water_around_ball_vs_params[3]) * vec4(position, 1.0);
    }
    
*/
static const char water_around_ball_vs_source_glsl330[404] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x33,0x30,0x0a,0x0a,0x75,0x6e,
    0x69,0x66,0x6f,0x72,0x6d,0x20,0x76,0x65,0x63,0x34,0x20,0x77,0x61,0x74,0x65,0x72,
    0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,0x5f,
    0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x34,0x5d,0x3b,0x0a,0x6f,0x75,0x74,0x20,0x76,
    0x65,0x63,0x32,0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,
    0x5f,0x63,0x6f,0x6f,0x72,0x64,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,
    0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x31,0x29,0x20,0x69,0x6e,0x20,
    0x76,0x65,0x63,0x32,0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,
    0x72,0x64,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,
    0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,0x69,0x6e,0x20,0x76,0x65,0x63,0x33,
    0x20,0x70,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x3b,0x0a,0x0a,0x76,0x6f,0x69,0x64,
    0x20,0x6d,0x61,0x69,0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x72,
    0x61,0x67,0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,
    0x20,0x3d,0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,
    0x3b,0x0a,0x20,0x20,0x20,0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,
    0x6e,0x20,0x3d,0x20,0x6d,0x61,0x74,0x34,0x28,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,
    0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,0x5f,0x70,0x61,
    0x72,0x61,0x6d,0x73,0x5b,0x30,0x5d,0x2c,0x20,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,
    0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,0x5f,0x70,0x61,
    0x72,0x61,0x6d,0x73,0x5b,0x31,0x5d,0x2c,0x20,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,
    0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,0x5f,0x70,0x61,
    0x72,0x61,0x6d,0x73,0x5b,0x32,0x5d,0x2c,0x20,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,
    0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,0x5f,0x70,0x61,
    0x72,0x61,0x6d,0x73,0x5b,0x33,0x5d,0x29,0x20,0x2a,0x20,0x76,0x65,0x63,0x34,0x28,
    0x70,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x2c,0x20,0x31,0x2e,0x30,0x29,0x3b,0x0a,
    0x7d,0x0a,0x0a,0x00,
};
/*
    #version 330
    
    uniform vec4 water_around_ball_fs_params[1];
    uniform sampler2D water_around_ball_noise_tex;
    
    in vec2 frag_texture_coord;
    layout(location = 0) out vec4 g_frag_color;
    
    void main()
    {
        vec4 _49 = texture(water_around_ball_noise_tex, (vec2(frag_texture_coord.x, frag_texture_coord.y) * 0.5) + vec2(0.20000000298023223876953125 * water_around_ball_fs_params[0].x));
        float _50 = _49.x;
        float _59 = length(vec2(frag_texture_coord.x - 0.5, frag_texture_coord.y - 0.5));
        float alpha = 0.800000011920928955078125;
        if (_59 > 0.23999999463558197021484375)
        {
            alpha = 0.0;
        }
        else
        {
            if (_59 > 0.20000000298023223876953125)
            {
                alpha = ((0.23999999463558197021484375 - _59) * 20.0) * _50;
            }
            else
            {
                if (_59 > 0.1599999964237213134765625)
                {
                    float _107 = (0.20000000298023223876953125 - _59) * 25.0;
                    alpha = 0.800000011920928955078125 * (((1.0 - _107) * _50) + _107);
                }
                else
                {
                    alpha = 0.800000011920928955078125;
                }
            }
        }
        g_frag_color = vec4(vec3(0.699999988079071044921875) * (0.89999997615814208984375 + (0.100000001490116119384765625 * _50)), alpha);
    }
    
*/
static const char water_around_ball_fs_source_glsl330[1278] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x33,0x30,0x0a,0x0a,0x75,0x6e,
    0x69,0x66,0x6f,0x72,0x6d,0x20,0x76,0x65,0x63,0x34,0x20,0x77,0x61,0x74,0x65,0x72,
    0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x66,0x73,0x5f,
    0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x31,0x5d,0x3b,0x0a,0x75,0x6e,0x69,0x66,0x6f,
    0x72,0x6d,0x20,0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,0x32,0x44,0x20,0x77,0x61,0x74,
    0x65,0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x6e,
    0x6f,0x69,0x73,0x65,0x5f,0x74,0x65,0x78,0x3b,0x0a,0x0a,0x69,0x6e,0x20,0x76,0x65,
    0x63,0x32,0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,
    0x63,0x6f,0x6f,0x72,0x64,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,
    0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,0x6f,0x75,0x74,0x20,
    0x76,0x65,0x63,0x34,0x20,0x67,0x5f,0x66,0x72,0x61,0x67,0x5f,0x63,0x6f,0x6c,0x6f,
    0x72,0x3b,0x0a,0x0a,0x76,0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x29,0x0a,
    0x7b,0x0a,0x20,0x20,0x20,0x20,0x76,0x65,0x63,0x34,0x20,0x5f,0x34,0x39,0x20,0x3d,
    0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x28,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,
    0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x6e,0x6f,0x69,0x73,0x65,
    0x5f,0x74,0x65,0x78,0x2c,0x20,0x28,0x76,0x65,0x63,0x32,0x28,0x66,0x72,0x61,0x67,
    0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,0x2e,0x78,
    0x2c,0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,
    0x6f,0x6f,0x72,0x64,0x2e,0x79,0x29,0x20,0x2a,0x20,0x30,0x2e,0x35,0x29,0x20,0x2b,
    0x20,0x76,0x65,0x63,0x32,0x28,0x30,0x2e,0x32,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
    0x32,0x39,0x38,0x30,0x32,0x33,0x32,0x32,0x33,0x38,0x37,0x36,0x39,0x35,0x33,0x31,
    0x32,0x35,0x20,0x2a,0x20,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,
    0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x66,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,
    0x5b,0x30,0x5d,0x2e,0x78,0x29,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,
    0x61,0x74,0x20,0x5f,0x35,0x30,0x20,0x3d,0x20,0x5f,0x34,0x39,0x2e,0x78,0x3b,0x0a,
    0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x5f,0x35,0x39,0x20,0x3d,0x20,
    0x6c,0x65,0x6e,0x67,0x74,0x68,0x28,0x76,0x65,0x63,0x32,0x28,0x66,0x72,0x61,0x67,
    0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,0x2e,0x78,
    0x20,0x2d,0x20,0x30,0x2e,0x35,0x2c,0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,
    0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,0x2e,0x79,0x20,0x2d,0x20,0x30,
    0x2e,0x35,0x29,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,
    0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x30,0x2e,0x38,0x30,0x30,0x30,0x30,0x30,
    0x30,0x31,0x31,0x39,0x32,0x30,0x39,0x32,0x38,0x39,0x35,0x35,0x30,0x37,0x38,0x31,
    0x32,0x35,0x3b,0x0a,0x20,0x20,0x20,0x20,0x69,0x66,0x20,0x28,0x5f,0x35,0x39,0x20,
    0x3e,0x20,0x30,0x2e,0x32,0x33,0x39,0x39,0x39,0x39,0x39,0x39,0x34,0x36,0x33,0x35,
    0x35,0x38,0x31,0x39,0x37,0x30,0x32,0x31,0x34,0x38,0x34,0x33,0x37,0x35,0x29,0x0a,
    0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x61,0x6c,
    0x70,0x68,0x61,0x20,0x3d,0x20,0x30,0x2e,0x30,0x3b,0x0a,0x20,0x20,0x20,0x20,0x7d,
    0x0a,0x20,0x20,0x20,0x20,0x65,0x6c,0x73,0x65,0x0a,0x20,0x20,0x20,0x20,0x7b,0x0a,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x69,0x66,0x20,0x28,0x5f,0x35,0x39,0x20,
    0x3e,0x20,0x30,0x2e,0x32,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x32,0x39,0x38,0x30,
    0x32,0x33,0x32,0x32,0x33,0x38,0x37,0x36,0x39,0x35,0x33,0x31,0x32,0x35,0x29,0x0a,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x28,0x28,
    0x30,0x2e,0x32,0x33,0x39,0x39,0x39,0x39,0x39,0x39,0x34,0x36,0x33,0x35,0x35,0x38,
    0x31,0x39,0x37,0x30,0x32,0x31,0x34,0x38,0x34,0x33,0x37,0x35,0x20,0x2d,0x20,0x5f,
    0x35,0x39,0x29,0x20,0x2a,0x20,0x32,0x30,0x2e,0x30,0x29,0x20,0x2a,0x20,0x5f,0x35,
    0x30,0x3b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7d,0x0a,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x65,0x6c,0x73,0x65,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x69,0x66,0x20,0x28,0x5f,0x35,0x39,0x20,0x3e,0x20,0x30,0x2e,0x31,0x35,0x39,0x39,
    0x39,0x39,0x39,0x39,0x36,0x34,0x32,0x33,0x37,0x32,0x31,0x33,0x31,0x33,0x34,0x37,
    0x36,0x35,0x36,0x32,0x35,0x29,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x5f,0x31,0x30,0x37,0x20,
    0x3d,0x20,0x28,0x30,0x2e,0x32,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x32,0x39,0x38,
    0x30,0x32,0x33,0x32,0x32,0x33,0x38,0x37,0x36,0x39,0x35,0x33,0x31,0x32,0x35,0x20,
    0x2d,0x20,0x5f,0x35,0x39,0x29,0x20,0x2a,0x20,0x32,0x35,0x2e,0x30,0x3b,0x0a,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x61,
    0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x30,0x2e,0x38,0x30,0x30,0x30,0x30,0x30,0x30,
    0x31,0x31,0x39,0x32,0x30,0x39,0x32,0x38,0x39,0x35,0x35,0x30,0x37,0x38,0x31,0x32,
    0x35,0x20,0x2a,0x20,0x28,0x28,0x28,0x31,0x2e,0x30,0x20,0x2d,0x20,0x5f,0x31,0x30,
    0x37,0x29,0x20,0x2a,0x20,0x5f,0x35,0x30,0x29,0x20,0x2b,0x20,0x5f,0x31,0x30,0x37,
    0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7d,
    0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x65,0x6c,0x73,
    0x65,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7b,0x0a,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x30,0x2e,0x38,0x30,0x30,0x30,0x30,0x30,
    0x30,0x31,0x31,0x39,0x32,0x30,0x39,0x32,0x38,0x39,0x35,0x35,0x30,0x37,0x38,0x31,
    0x32,0x35,0x3b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x7d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7d,0x0a,0x20,0x20,0x20,0x20,
    0x7d,0x0a,0x20,0x20,0x20,0x20,0x67,0x5f,0x66,0x72,0x61,0x67,0x5f,0x63,0x6f,0x6c,
    0x6f,0x72,0x20,0x3d,0x20,0x76,0x65,0x63,0x34,0x28,0x76,0x65,0x63,0x33,0x28,0x30,
    0x2e,0x36,0x39,0x39,0x39,0x39,0x39,0x39,0x38,0x38,0x30,0x37,0x39,0x30,0x37,0x31,
    0x30,0x34,0x34,0x39,0x32,0x31,0x38,0x37,0x35,0x29,0x20,0x2a,0x20,0x28,0x30,0x2e,
    0x38,0x39,0x39,0x39,0x39,0x39,0x39,0x37,0x36,0x31,0x35,0x38,0x31,0x34,0x32,0x30,
    0x38,0x39,0x38,0x34,0x33,0x37,0x35,0x20,0x2b,0x20,0x28,0x30,0x2e,0x31,0x30,0x30,
    0x30,0x30,0x30,0x30,0x30,0x31,0x34,0x39,0x30,0x31,0x31,0x36,0x31,0x31,0x39,0x33,
    0x38,0x34,0x37,0x36,0x35,0x36,0x32,0x35,0x20,0x2a,0x20,0x5f,0x35,0x30,0x29,0x29,
    0x2c,0x20,0x61,0x6c,0x70,0x68,0x61,0x29,0x3b,0x0a,0x7d,0x0a,0x0a,0x00,
};
/*
    #version 300 es
    
    uniform vec4 water_around_ball_vs_params[4];
    out vec2 frag_texture_coord;
    layout(location = 1) in vec2 texture_coord;
    layout(location = 0) in vec3 position;
    
    void main()
    {
        frag_texture_coord = texture_coord;
        gl_Position = mat4(water_around_ball_vs_params[0], water_around_ball_vs_params[1], water_around_ball_vs_params[2], water_around_ball_vs_params[3]) * vec4(position, 1.0);
    }
    
*/
static const char water_around_ball_vs_source_glsl300es[407] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x30,0x30,0x20,0x65,0x73,0x0a,
    0x0a,0x75,0x6e,0x69,0x66,0x6f,0x72,0x6d,0x20,0x76,0x65,0x63,0x34,0x20,0x77,0x61,
    0x74,0x65,0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,
    0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x34,0x5d,0x3b,0x0a,0x6f,0x75,
    0x74,0x20,0x76,0x65,0x63,0x32,0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,
    0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,
    0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x31,0x29,0x20,
    0x69,0x6e,0x20,0x76,0x65,0x63,0x32,0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,
    0x63,0x6f,0x6f,0x72,0x64,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,
    0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,0x69,0x6e,0x20,0x76,
    0x65,0x63,0x33,0x20,0x70,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x3b,0x0a,0x0a,0x76,
    0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,
    0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,
    0x6f,0x72,0x64,0x20,0x3d,0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,
    0x6f,0x72,0x64,0x3b,0x0a,0x20,0x20,0x20,0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,
    0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x6d,0x61,0x74,0x34,0x28,0x77,0x61,0x74,0x65,
    0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,
    0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x30,0x5d,0x2c,0x20,0x77,0x61,0x74,0x65,
    0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,
    0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x31,0x5d,0x2c,0x20,0x77,0x61,0x74,0x65,
    0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,
    0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x32,0x5d,0x2c,0x20,0x77,0x61,0x74,0x65,
    0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x76,0x73,
    0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x33,0x5d,0x29,0x20,0x2a,0x20,0x76,0x65,
    0x63,0x34,0x28,0x70,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x2c,0x20,0x31,0x2e,0x30,
    0x29,0x3b,0x0a,0x7d,0x0a,0x0a,0x00,
};
/*
    #version 300 es
    precision mediump float;
    precision highp int;
    
    uniform highp vec4 water_around_ball_fs_params[1];
    uniform highp sampler2D water_around_ball_noise_tex;
    
    in highp vec2 frag_texture_coord;
    layout(location = 0) out highp vec4 g_frag_color;
    
    void main()
    {
        highp vec4 _49 = texture(water_around_ball_noise_tex, (vec2(frag_texture_coord.x, frag_texture_coord.y) * 0.5) + vec2(0.20000000298023223876953125 * water_around_ball_fs_params[0].x));
        highp float _50 = _49.x;
        highp float _59 = length(vec2(frag_texture_coord.x - 0.5, frag_texture_coord.y - 0.5));
        highp float alpha = 0.800000011920928955078125;
        if (_59 > 0.23999999463558197021484375)
        {
            alpha = 0.0;
        }
        else
        {
            if (_59 > 0.20000000298023223876953125)
            {
                alpha = ((0.23999999463558197021484375 - _59) * 20.0) * _50;
            }
            else
            {
                if (_59 > 0.1599999964237213134765625)
                {
                    highp float _107 = (0.20000000298023223876953125 - _59) * 25.0;
                    alpha = 0.800000011920928955078125 * (((1.0 - _107) * _50) + _107);
                }
                else
                {
                    alpha = 0.800000011920928955078125;
                }
            }
        }
        g_frag_color = vec4(vec3(0.699999988079071044921875) * (0.89999997615814208984375 + (0.100000001490116119384765625 * _50)), alpha);
    }
    
*/
static const char water_around_ball_fs_source_glsl300es[1381] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x30,0x30,0x20,0x65,0x73,0x0a,
    0x70,0x72,0x65,0x63,0x69,0x73,0x69,0x6f,0x6e,0x20,0x6d,0x65,0x64,0x69,0x75,0x6d,
    0x70,0x20,0x66,0x6c,0x6f,0x61,0x74,0x3b,0x0a,0x70,0x72,0x65,0x63,0x69,0x73,0x69,
    0x6f,0x6e,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x69,0x6e,0x74,0x3b,0x0a,0x0a,0x75,
    0x6e,0x69,0x66,0x6f,0x72,0x6d,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x76,0x65,0x63,
    0x34,0x20,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,
    0x61,0x6c,0x6c,0x5f,0x66,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x31,0x5d,
    0x3b,0x0a,0x75,0x6e,0x69,0x66,0x6f,0x72,0x6d,0x20,0x68,0x69,0x67,0x68,0x70,0x20,
    0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,0x32,0x44,0x20,0x77,0x61,0x74,0x65,0x72,0x5f,
    0x61,0x72,0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x6e,0x6f,0x69,0x73,
    0x65,0x5f,0x74,0x65,0x78,0x3b,0x0a,0x0a,0x69,0x6e,0x20,0x68,0x69,0x67,0x68,0x70,
    0x20,0x76,0x65,0x63,0x32,0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,0x75,
    0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,
    0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,0x6f,
    0x75,0x74,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x76,0x65,0x63,0x34,0x20,0x67,0x5f,
    0x66,0x72,0x61,0x67,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x3b,0x0a,0x0a,0x76,0x6f,0x69,
    0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x68,
    0x69,0x67,0x68,0x70,0x20,0x76,0x65,0x63,0x34,0x20,0x5f,0x34,0x39,0x20,0x3d,0x20,
    0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x28,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,0x72,
    0x6f,0x75,0x6e,0x64,0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x6e,0x6f,0x69,0x73,0x65,0x5f,
    0x74,0x65,0x78,0x2c,0x20,0x28,0x76,0x65,0x63,0x32,0x28,0x66,0x72,0x61,0x67,0x5f,
    0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,0x2e,0x78,0x2c,
    0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,0x63,0x6f,
    0x6f,0x72,0x64,0x2e,0x79,0x29,0x20,0x2a,0x20,0x30,0x2e,0x35,0x29,0x20,0x2b,0x20,
    0x76,0x65,0x63,0x32,0x28,0x30,0x2e,0x32,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x32,
    0x39,0x38,0x30,0x32,0x33,0x32,0x32,0x33,0x38,0x37,0x36,0x39,0x35,0x33,0x31,0x32,
    0x35,0x20,0x2a,0x20,0x77,0x61,0x74,0x65,0x72,0x5f,0x61,0x72,0x6f,0x75,0x6e,0x64,
    0x5f,0x62,0x61,0x6c,0x6c,0x5f,0x66,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,
    0x30,0x5d,0x2e,0x78,0x29,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x68,0x69,0x67,0x68,
    0x70,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x5f,0x35,0x30,0x20,0x3d,0x20,0x5f,0x34,
    0x39,0x2e,0x78,0x3b,0x0a,0x20,0x20,0x20,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x66,
    0x6c,0x6f,0x61,0x74,0x20,0x5f,0x35,0x39,0x20,0x3d,0x20,0x6c,0x65,0x6e,0x67,0x74,
    0x68,0x28,0x76,0x65,0x63,0x32,0x28,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,
    0x75,0x72,0x65,0x5f,0x63,0x6f,0x6f,0x72,0x64,0x2e,0x78,0x20,0x2d,0x20,0x30,0x2e,
    0x35,0x2c,0x20,0x66,0x72,0x61,0x67,0x5f,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x5f,
    0x63,0x6f,0x6f,0x72,0x64,0x2e,0x79,0x20,0x2d,0x20,0x30,0x2e,0x35,0x29,0x29,0x3b,
    0x0a,0x20,0x20,0x20,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x66,0x6c,0x6f,0x61,0x74,
    0x20,0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x30,0x2e,0x38,0x30,0x30,0x30,0x30,
    0x30,0x30,0x31,0x31,0x39,0x32,0x30,0x39,0x32,0x38,0x39,0x35,0x35,0x30,0x37,0x38,
    0x31,0x32,0x35,0x3b,0x0a,0x20,0x20,0x20,0x20,0x69,0x66,0x20,0x28,0x5f,0x35,0x39,
    0x20,0x3e,0x20,0x30,0x2e,0x32,0x33,0x39,0x39,0x39,0x39,0x39,0x39,0x34,0x36,0x33,
    0x35,0x35,0x38,0x31,0x39,0x37,0x30,0x32,0x31,0x34,0x38,0x34,0x33,0x37,0x35,0x29,
    0x0a,0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x61,
    0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x30,0x2e,0x30,0x3b,0x0a,0x20,0x20,0x20,0x20,
    0x7d,0x0a,0x20,0x20,0x20,0x20,0x65,0x6c,0x73,0x65,0x0a,0x20,0x20,0x20,0x20,0x7b,
    0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x69,0x66,0x20,0x28,0x5f,0x35,0x39,
    0x20,0x3e,0x20,0x30,0x2e,0x32,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x32,0x39,0x38,
    0x30,0x32,0x33,0x32,0x32,0x33,0x38,0x37,0x36,0x39,0x35,0x33,0x31,0x32,0x35,0x29,
    0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x28,
    0x28,0x30,0x2e,0x32,0x33,0x39,0x39,0x39,0x39,0x39,0x39,0x34,0x36,0x33,0x35,0x35,
    0x38,0x31,0x39,0x37,0x30,0x32,0x31,0x34,0x38,0x34,0x33,0x37,0x35,0x20,0x2d,0x20,
    0x5f,0x35,0x39,0x29,0x20,0x2a,0x20,0x32,0x30,0x2e,0x30,0x29,0x20,0x2a,0x20,0x5f,
    0x35,0x30,0x3b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7d,0x0a,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x65,0x6c,0x73,0x65,0x0a,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x69,0x66,0x20,0x28,0x5f,0x35,0x39,0x20,0x3e,0x20,0x30,0x2e,0x31,0x35,0x39,
    0x39,0x39,0x39,0x39,0x39,0x36,0x34,0x32,0x33,0x37,0x32,0x31,0x33,0x31,0x33,0x34,
    0x37,0x36,0x35,0x36,0x32,0x35,0x29,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x66,0x6c,0x6f,0x61,
    0x74,0x20,0x5f,0x31,0x30,0x37,0x20,0x3d,0x20,0x28,0x30,0x2e,0x32,0x30,0x30,0x30,
    0x30,0x30,0x30,0x30,0x32,0x39,0x38,0x30,0x32,0x33,0x32,0x32,0x33,0x38,0x37,0x36,
    0x39,0x35,0x33,0x31,0x32,0x35,0x20,0x2d,0x20,0x5f,0x35,0x39,0x29,0x20,0x2a,0x20,
    0x32,0x35,0x2e,0x30,0x3b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x30,0x2e,
    0x38,0x30,0x30,0x30,0x30,0x30,0x30,0x31,0x31,0x39,0x32,0x30,0x39,0x32,0x38,0x39,
    0x35,0x35,0x30,0x37,0x38,0x31,0x32,0x35,0x20,0x2a,0x20,0x28,0x28,0x28,0x31,0x2e,
    0x30,0x20,0x2d,0x20,0x5f,0x31,0x30,0x37,0x29,0x20,0x2a,0x20,0x5f,0x35,0x30,0x29,
    0x20,0x2b,0x20,0x5f,0x31,0x30,0x37,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x7d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x65,0x6c,0x73,0x65,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x30,
    0x2e,0x38,0x30,0x30,0x30,0x30,0x30,0x30,0x31,0x31,0x39,0x32,0x30,0x39,0x32,0x38,
    0x39,0x35,0x35,0x30,0x37,0x38,0x31,0x32,0x35,0x3b,0x0a,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x7d,0x0a,0x20,0x20,0x20,0x20,0x7d,0x0a,0x20,0x20,0x20,0x20,0x67,0x5f,0x66,
    0x72,0x61,0x67,0x5f,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x76,0x65,0x63,0x34,
    0x28,0x76,0x65,0x63,0x33,0x28,0x30,0x2e,0x36,0x39,0x39,0x39,0x39,0x39,0x39,0x38,
    0x38,0x30,0x37,0x39,0x30,0x37,0x31,0x30,0x34,0x34,0x39,0x32,0x31,0x38,0x37,0x35,
    0x29,0x20,0x2a,0x20,0x28,0x30,0x2e,0x38,0x39,0x39,0x39,0x39,0x39,0x39,0x37,0x36,
    0x31,0x35,0x38,0x31,0x34,0x32,0x30,0x38,0x39,0x38,0x34,0x33,0x37,0x35,0x20,0x2b,
    0x20,0x28,0x30,0x2e,0x31,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x31,0x34,0x39,0x30,
    0x31,0x31,0x36,0x31,0x31,0x39,0x33,0x38,0x34,0x37,0x36,0x35,0x36,0x32,0x35,0x20,
    0x2a,0x20,0x5f,0x35,0x30,0x29,0x29,0x2c,0x20,0x61,0x6c,0x70,0x68,0x61,0x29,0x3b,
    0x0a,0x7d,0x0a,0x0a,0x00,
};
#if !defined(SOKOL_GFX_INCLUDED)
  #error "Please include sokol_gfx.h before water_around_ball.glsl.h"
#endif
static inline const sg_shader_desc* water_around_ball_shader_desc(sg_backend backend) {
  if (backend == SG_BACKEND_GLCORE33) {
    static sg_shader_desc desc;
    static bool valid;
    if (!valid) {
      valid = true;
      desc.attrs[0].name = "position";
      desc.attrs[1].name = "texture_coord";
      desc.vs.source = water_around_ball_vs_source_glsl330;
      desc.vs.entry = "main";
      desc.vs.uniform_blocks[0].size = 64;
      desc.vs.uniform_blocks[0].uniforms[0].name = "water_around_ball_vs_params";
      desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
      desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
      desc.fs.source = water_around_ball_fs_source_glsl330;
      desc.fs.entry = "main";
      desc.fs.uniform_blocks[0].size = 16;
      desc.fs.uniform_blocks[0].uniforms[0].name = "water_around_ball_fs_params";
      desc.fs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
      desc.fs.uniform_blocks[0].uniforms[0].array_count = 1;
      desc.fs.images[0].name = "water_around_ball_noise_tex";
      desc.fs.images[0].image_type = SG_IMAGETYPE_2D;
      desc.fs.images[0].sampler_type = SG_SAMPLERTYPE_FLOAT;
      desc.label = "water_around_ball_shader";
    }
    return &desc;
  }
  if (backend == SG_BACKEND_GLES3) {
    static sg_shader_desc desc;
    static bool valid;
    if (!valid) {
      valid = true;
      desc.attrs[0].name = "position";
      desc.attrs[1].name = "texture_coord";
      desc.vs.source = water_around_ball_vs_source_glsl300es;
      desc.vs.entry = "main";
      desc.vs.uniform_blocks[0].size = 64;
      desc.vs.uniform_blocks[0].uniforms[0].name = "water_around_ball_vs_params";
      desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
      desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
      desc.fs.source = water_around_ball_fs_source_glsl300es;
      desc.fs.entry = "main";
      desc.fs.uniform_blocks[0].size = 16;
      desc.fs.uniform_blocks[0].uniforms[0].name = "water_around_ball_fs_params";
      desc.fs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
      desc.fs.uniform_blocks[0].uniforms[0].array_count = 1;
      desc.fs.images[0].name = "water_around_ball_noise_tex";
      desc.fs.images[0].image_type = SG_IMAGETYPE_2D;
      desc.fs.images[0].sampler_type = SG_SAMPLERTYPE_FLOAT;
      desc.label = "water_around_ball_shader";
    }
    return &desc;
  }
  return 0;
}
