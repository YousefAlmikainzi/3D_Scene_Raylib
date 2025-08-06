#version 330

//vertex to fragment
//in
in vec2 o_uv;
in vec3 o_normal;
in vec4 fragColor;
in vec3 world_pos;

//out
out vec4 finalColor;

//uniform
uniform vec3 viewPos;

float saturation(float v)
{
    return clamp(v, 0.0, 1.0);
}

void main()
{
    vec3 Normals = normalize(o_normal);
    //Color
    vec3 color = vec3(.15,.3,.45);
    
    //ambient
    vec3 ambient = color * 0.5;
    
    //diffuse
    vec3 lightDir = normalize(vec3(0, 1, 0));
    float diffuse = max(dot(Normals, lightDir), 0);
    float st = saturation(diffuse);
    
    //specular
    vec3 viewDir = normalize(viewPos - world_pos);
    vec3 halfVec = normalize(viewDir + lightDir);
    float NdotH = pow(max(dot(Normals, halfVec), 0.0), 5000.0);
    vec3 specular = NdotH * vec3(1,1,1);
    
    //result
    vec3 diffusedColor = (color * st);
    vec3 result = diffusedColor + ambient + specular;
    
    finalColor = vec4(result, 1);
}