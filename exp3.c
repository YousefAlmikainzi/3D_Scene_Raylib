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
    
    int floc = GetShaderLocation(skyboxShader, "Front");
    int bloc = GetShaderLocation(skyboxShader, "Back");
    int uloc = GetShaderLocation(skyboxShader, "Up");
    int dloc = GetShaderLocation(skyboxShader, "Down");
    int rloc = GetShaderLocation(skyboxShader, "Right");
    int lloc = GetShaderLocation(skyboxShader, "Left");
    
    printf("floc %d\n", floc);
    printf("bloc %d\n", bloc);
    printf("uloc %d\n", uloc);
    printf("dloc %d\n", dloc);
    printf("rloc %d\n", rloc);
    printf("lloc %d\n", lloc);
    
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
        BeginMode3D(camera);
            UpdateCamera(&camera, CAMERA_FREE);
            DrawCube((Vector3){10, 0, 10}, 10, 10, 10, YELLOW);
            
            rlDisableBackfaceCulling();
            
            SetShaderValueTexture(skyboxShader, floc, ftTexture);
            SetShaderValueTexture(skyboxShader, bloc, bkTexture);

            SetShaderValueTexture(skyboxShader, rloc, rtTexture);
            SetShaderValueTexture(skyboxShader, lloc, lfTexture);

            SetShaderValueTexture(skyboxShader, uloc, upTexture);
            SetShaderValueTexture(skyboxShader, dloc, dnTexture);

            DrawModel(cube, (Vector3){0,0,0}, 10.0f, WHITE);
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
