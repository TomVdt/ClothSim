#version 330 core

in vec4 vertex;

uniform vec4 color;
uniform mat4 m_matrix;
uniform mat4 pv_matrix;

out vec4 varying_color;

void main() {
    varying_color = color;

    vec4 res = pv_matrix * m_matrix * vertex;
    gl_Position = res;
}
