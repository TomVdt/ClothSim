#version 330 core

in vec4 vertex;

uniform vec4 color;
uniform mat4 pv_matrix;
uniform mat4 m_matrix;

// out vec4 varying_pos;
out vec4 varying_color;

void main() {
    // varying_pos = m_matrix * varying_pos;
    varying_color = color;

    gl_Position = pv_matrix * m_matrix * vertex;
}
