#version 330

//vertex to fragment
//in
in vec2 o_uv;
in vec3 o_normal;

//out
out vec4 finalColor;

//uniform
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;


//regular

void main()
{
    vec3 ftFace = vec3(0.0, 0.0, 1.0);
    float ft = dot(o_normal, ftFace);
        
    vec3 bkFace = vec3(0.0, 0.0, -1.0);
    float bk = dot(o_normal, bkFace);
        
    vec3 upFace = vec3(0.0, 1.0, 0.0);
    float up = dot(o_normal, upFace);

    vec3 dnFace = vec3(0.0, -1.0, 0.0);
    float dn = dot(o_normal, dnFace);

    vec3 rtFace = vec3(1.0, 0.0, 0.0);
    float rt = dot(o_normal, rtFace);
    
    vec3 lfFace = vec3(-1.0, 0.0, 0.0);
    float lf = dot(o_normal, lfFace);

    vec4 ftTextured = texture(texture0, o_uv);
    vec4 bkTextured = texture(texture1, o_uv);
    vec4 upTextured = texture(texture2, o_uv);
    vec4 dnTextured = texture(texture3, o_uv);
    vec4 rtTextured = texture(texture4, o_uv);
    vec4 lfTextured = texture(texture5, o_uv);
    
    vec3 ftResult = ftTextured.rgb * ftFace;
    vec3 bkResult = bkTextured.rgb * bkFace;
    vec3 upResult = upTextured.rgb * upFace;
    vec3 dnResult = dnTextured.rgb * dnFace;
    vec3 rtResult = rtTextured.rgb * rtFace;
    vec3 lfResult = lfTextured.rgb * lfFace;
    
    vec3 skybox = ftResult + bkResult + upResult + dnResult + rtResult + lfResult;
    
    finalColor = vec4(skybox, 1);
}