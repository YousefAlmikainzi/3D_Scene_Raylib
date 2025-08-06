#include "raylib.h"
#include "rlgl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 

#define SCREEN_SIZE 1000

//example for using point for vector
typedef struct point
{
    float x;
    float y;
}point;

typedef union VectorPoint
{
    point point;
    Vector2 vector;
} VectorPoint;

//2D things
Vector2 playerMovement = {500, 500};
float speed = 300;
bool see2d = false;
void Grid();
void Control();

int main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Window");
    SetTargetFPS(60);
    //Camera
    Camera3D camera = {
        .position = {0.0f, 10.0f, 10.0f},
        .target = {0.0f, 0.0f, 1.0f},
        .up = {0.0f, 1.0f, 0.0f},
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };
    //3D stuff
    //Loading Texture and Shading
    
    Shader skyboxShader = LoadShader("skybox.vs", "Try2.fs");
    
    char* ftPic = "textures/skybox/ft.jpg";
    char* bkPic = "textures/skybox/bk.jpg";
    char* upPic = "textures/skybox/up.jpg";
    char* dnPic = "textures/skybox/dn.jpg";
    char* rtPic = "textures/skybox/rt.jpg";
    char* lfPic = "textures/skybox/lf.jpg";
    
    Texture2D ftTexture = LoadTexture(ftPic);
    Texture2D bkTexture = LoadTexture(bkPic);
    Texture2D upTexture = LoadTexture(upPic);
    Texture2D dnTexture = LoadTexture(dnPic);
    Texture2D rtTexture = LoadTexture(rtPic);
    Texture2D lfTexture = LoadTexture(lfPic);
    
    Model cube = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
    
    cube.materials[0].shader = skyboxShader;
    cube.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = ftTexture;
    cube.materials[0].maps[MATERIAL_MAP_ALBEDO + 1].texture = bkTexture;
    cube.materials[0].maps[MATERIAL_MAP_ALBEDO + 2].texture = upTexture;
    cube.materials[0].maps[MATERIAL_MAP_ALBEDO + 3].texture = dnTexture;
    cube.materials[0].maps[MATERIAL_MAP_ALBEDO + 4].texture = rtTexture;
    cube.materials[0].maps[MATERIAL_MAP_ALBEDO + 5].texture = lfTexture;
    
    
    skyboxShader.locs[SHADER_LOC_MAP_ALBEDO]     = GetShaderLocation(skyboxShader, "Front");
    skyboxShader.locs[SHADER_LOC_MAP_ALBEDO + 1] = GetShaderLocation(skyboxShader, "Back");
    skyboxShader.locs[SHADER_LOC_MAP_ALBEDO + 2] = GetShaderLocation(skyboxShader, "Up");
    skyboxShader.locs[SHADER_LOC_MAP_ALBEDO + 3] = GetShaderLocation(skyboxShader, "Down");
    skyboxShader.locs[SHADER_LOC_MAP_ALBEDO + 4] = GetShaderLocation(skyboxShader, "Right");
    skyboxShader.locs[SHADER_LOC_MAP_ALBEDO + 5] = GetShaderLocation(skyboxShader, "Left");
    
    //a making of an object
    Shader diffuseShader = LoadShader("Vertex_Standard.vs", "Diffuse_Specular.fs");
    Model sphere = LoadModelFromMesh(GenMeshSphere(5,100,100));
    sphere.materials[0].shader = diffuseShader;
    skyboxShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(diffuseShader, "viewPos");
    
    printf("camera loc %d\n", skyboxShader.locs[SHADER_LOC_MATRIX_VIEW]);
    for(int i = 0 ; i < RL_MAX_SHADER_LOCATIONS ; i++)
    {
        if(skyboxShader.locs[i] != -1)
            printf("SHADER LOC AT %d = %d\n", i, skyboxShader.locs[i]);
    }
    printf("POSITION LOC %d\n", skyboxShader.locs[SHADER_LOC_VERTEX_POSITION]);
    printf("TEXCOORD1 LOC %d\n", skyboxShader.locs[SHADER_LOC_VERTEX_TEXCOORD01]);
    printf("NORMAL LOC %d\n", skyboxShader.locs[SHADER_LOC_VERTEX_NORMAL]);
    
    DisableCursor();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        UpdateCamera(&camera, CAMERA_FREE);
        
        BeginMode3D(camera);
            // BeginShaderMode(diffuseShader);
            
                SetShaderValue(diffuseShader, skyboxShader.locs[SHADER_LOC_VECTOR_VIEW], &camera.position, SHADER_UNIFORM_VEC3);
            
                DrawModel(sphere, (Vector3){10.0f,10.0f,10.0f}, 1.0f, WHITE);
                
            // EndShaderMode();
                
            rlDisableBackfaceCulling();
            DrawModel(cube, (Vector3){0,0,0}, 1000.0f, WHITE);
            rlEnableBackfaceCulling();
        EndMode3D();
        
        EndDrawing();
    }
    
    UnloadTexture(ftTexture);
    UnloadTexture(bkTexture);
    UnloadTexture(upTexture);
    UnloadTexture(dnTexture);
    UnloadTexture(rtTexture);
    UnloadTexture(lfTexture);
    UnloadShader(skyboxShader);
    UnloadModel(cube);
    CloseWindow();
    return 0;
}
