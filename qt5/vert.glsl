#version 330 core

in vec4 vertex;
in vec4 color;
in vec2 tex_coord;

uniform mat4 pv_matrix;
uniform mat4 m_matrix;
uniform float time;

out vec4 varying_pos;
out vec4 varying_color;
out vec2 varying_tex_coord;

void main() {
    varying_pos = vertex;

    // varying_pos.x += (sin((time / 180.0f) * 3.141579f));
    // varying_pos.z += (sin((time / 180.0f) * 3.141579f));
    // varying_pos.y += (cos(((time + time) / 180.0f) * 3.141579f) - 1.0f);

    varying_pos = m_matrix * varying_pos; 
    gl_Position = pv_matrix * varying_pos;
    varying_color = color;
    varying_tex_coord = tex_coord;
}
