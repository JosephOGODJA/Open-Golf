@ctype mat4 mat4
@ctype vec4 vec4
@ctype vec3 vec3
@ctype vec2 vec2

@vs environment_vs
uniform environment_vs_params {
    mat4 model_mat;
    mat4 proj_view_mat;
};

in vec3 position;
in vec2 texturecoord;
in vec3 normal;
in vec2 lightmap_uv;

out vec3 frag_position;
out vec2 frag_texturecoord;
out vec3 frag_normal;
out vec2 frag_lightmap_uv;

void main() {
    frag_position = (model_mat * vec4(position, 1.0)).xyz;
    frag_texturecoord = texturecoord;
    frag_normal = normal;
    frag_lightmap_uv = lightmap_uv;
    gl_Position = proj_view_mat * model_mat * vec4(position, 1.0);
}
@end

@fs environment_fs
uniform sampler2D kd_texture;
uniform sampler2D lightmap_texture;

in vec3 frag_position;
in vec2 frag_texturecoord;
in vec3 frag_normal;
in vec2 frag_lightmap_uv;

out vec4 g_frag_color;

void main() {
    float gi = texture(lightmap_texture, frag_lightmap_uv).x; 
    vec3 color = texture(kd_texture, frag_texturecoord).xyz; 
    color = color + 0.001 * (frag_normal.xyz + frag_position.xyz);
    g_frag_color = vec4(gi * color, 1.0);
}
@end

@program environment environment_vs environment_fs
