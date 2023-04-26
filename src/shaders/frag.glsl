#version 330 core

// in vec4 varying_pos;
in vec4 varying_color;

out vec4 out_color;

// const vec3 light = normalize(vec3(1, 1, 1));

void main() {
    // out_color = vec4(1.0, 1.0, 1.0, 1.0);
    out_color = varying_color;
    out_color.w = 1.0;
}
