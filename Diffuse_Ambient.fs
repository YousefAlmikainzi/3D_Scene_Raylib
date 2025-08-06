#version 330

//vertex to fragment
//in
in vec2 o_uv;
in vec3 o_normal;
in vec4 fragColor;

//out
out vec4 finalColor;

//uniform


float saturation(float v)
{
    return clamp(v, 0.0, 1.0);
}

vec3 saturation(vec3 v)
{
    return clamp(v, 0.0, 1.0);
}

void main()
{
    vec3 dir = normalize(vec3(.5, .5, 0));
    float diffuse = dot(o_normal, dir);
    float st = saturation(diffuse);
    finalColor = (vec4(1,0,0,1) * st) + vec4(.5,0,0,1);
}