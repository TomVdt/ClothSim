#version 330 core

in vec4 varying_pos;
in vec4 varying_color;
in vec2 varying_tex_coord;

uniform sampler2D texture;

out vec4 out_color;

const vec3 light = normalize(vec3(1, 1, 1));

void main() {
    out_color = texture2D(texture, varying_tex_coord) * varying_color;
    out_color = clamp(dot(light, normalize(varying_pos.xyz)), 0.4, 1) * out_color;
    // out_color = varying_color;
    // out_color = vec4(1.0);
    out_color.w = 1.0;
}
