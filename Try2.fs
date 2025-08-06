#version 330

//vertex to fragment
//in
in vec2 o_uv;
in vec3 o_normal;
in vec4 fragColor;

//out
out vec4 finalColor;

//uniform
uniform sampler2D Front;
uniform sampler2D Back;
uniform sampler2D Up;
uniform sampler2D Down;
uniform sampler2D Right;
uniform sampler2D Left;

//regular

//functions
float saturation(float v)
{
    return clamp(v, 0.0, 1.0);
}

void main()
{
    vec3 ftFace = vec3(1.0, 0.0, 0.0);
    float ft = dot(o_normal, ftFace);
    float stFt = saturation(ft);
    
    vec3 bkFace = vec3(-1.0, 0.0, 0.0);
    float bk = dot(o_normal, bkFace);
    float stBk = saturation(bk);
    
    vec3 upFace = vec3(0.0, 1.0, 0.0);
    float up = dot(o_normal, upFace);
    float stUp = saturation(up);

    vec3 dnFace = vec3(0.0, -1.0, 0.0);
    float dn = dot(o_normal, dnFace);
    float stDn = saturation(dn);
    
    vec3 rtFace = vec3(0.0, 0.0, 1.0);
    float rt = dot(o_normal, rtFace);
    float stRt = saturation(rt);
    
    vec3 lfFace = vec3(0.0, 0.0, -1.0);
    float lf = dot(o_normal, lfFace);
    float stLf = saturation(lf);
    
    vec4 ftTextured = texture(Front, o_uv);
    vec4 bkTextured = texture(Back, o_uv);
    vec4 upTextured = texture(Up, vec2(o_uv.x, 1 - o_uv.y));
    vec4 dnTextured = texture(Down, vec2(1 - o_uv.x, o_uv.y));
    vec4 rtTextured = texture(Right, o_uv);
    vec4 lfTextured = texture(Left, o_uv);

    vec4 result =  (ftTextured * stFt) + (bkTextured * stBk)+ (upTextured * stUp)+ (dnTextured * stDn)+ (rtTextured * stRt)+ (lfTextured * stLf);
    
    finalColor = result;
}