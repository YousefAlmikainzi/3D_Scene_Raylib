#version 330

//mesh data
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in vec3 v_normal;

//output
out vec2 o_uv;
out vec3 o_normal;

//uniform
uniform mat4 mvp;
uniform mat4 matNormal;

void main()
{
    o_uv = v_uv;
    o_normal = normalize(vec3(matNormal * vec4(v_normal, 0.0)));
    gl_Position = mvp * vec4(position, 1.0);
}