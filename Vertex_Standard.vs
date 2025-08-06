#version 330

//mesh data
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec4 vertexColor;

//output
out vec2 o_uv;
out vec3 o_normal;
out vec4 fragColor;
out vec3 world_pos;

//uniform
uniform mat4 mvp;
uniform mat4 matNormal;
uniform mat4 matModel;

void main()
{
    o_uv = vertexTexCoord;
    fragColor = vertexColor;
    o_normal = normalize(vec3(matNormal * vec4(vertexNormal, 0.0)));
    vec4 worldVec4 = matModel * vec4(vertexPosition, 1.0);
    world_pos = worldVec4.xyz;
    
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}