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
    Shader skyboxShader = LoadShader("skybox.vs", "skybox.fs");
    
    SetShaderValueTexture(skyboxShader, GetShaderLocation(skyboxShader, "texture0"), ftTexture);
    SetShaderValueTexture(skyboxShader, GetShaderLocation(skyboxShader, "texture1"), bkTexture);
    SetShaderValueTexture(skyboxShader, GetShaderLocation(skyboxShader, "texture2"), upTexture);
    SetShaderValueTexture(skyboxShader, GetShaderLocation(skyboxShader, "texture3"), dnTexture);
    SetShaderValueTexture(skyboxShader, GetShaderLocation(skyboxShader, "texture4"), rtTexture);
    SetShaderValueTexture(skyboxShader, GetShaderLocation(skyboxShader, "texture5"), lfTexture);
    
    printf("Cube has %d mats\n", cube.materialCount);
    cube.materials[0].shader = skyboxShader;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
            UpdateCamera(&camera, CAMERA_FREE);
            DrawCube((Vector3){10, 0, 10}, 10, 10, 10, YELLOW);
            rlDisableBackfaceCulling();
            DrawModel(cube, (Vector3){0,0,0}, 1000.0f, WHITE);
            rlEnableBackfaceCulling();
        EndMode3D();
        
        //all 2D stuff
        if(IsKeyDown(KEY_SPACE))
        {
            see2d = true;
        } else if(IsKeyDown(KEY_P))
        {
            see2d = false;
        }
        if(see2d)
        {
            DrawCircle(playerMovement.x, playerMovement.y, 20, BLUE);
            Grid();
            DrawTriangle((Vector2){((float)SCREEN_SIZE/10) * 5,((float)SCREEN_SIZE/10) * 4}, (Vector2){((float)SCREEN_SIZE/10) * 5,((float)SCREEN_SIZE/10) * 5}, (Vector2){((float)SCREEN_SIZE/10) * 6,((float)SCREEN_SIZE/10) * 5}, (Color){75,75,75,255});
            DrawTriangle((Vector2){((float)SCREEN_SIZE/10) * 5,((float)SCREEN_SIZE/10) * 6}, (Vector2){((float)SCREEN_SIZE/10) * 5,((float)SCREEN_SIZE/10) * 5}, (Vector2){((float)SCREEN_SIZE/10) * 4,((float)SCREEN_SIZE/10) * 5}, (Color){15,15,15,255});
            DrawTriangle((Vector2){((float)SCREEN_SIZE/10) * 4,((float)SCREEN_SIZE/10) * 5}, (Vector2){((float)SCREEN_SIZE/10) * 5,((float)SCREEN_SIZE/10) * 5}, (Vector2){((float)SCREEN_SIZE/10) * 5,((float)SCREEN_SIZE/10) * 4}, (Color){50,50,50,255});
            DrawTriangle((Vector2){((float)SCREEN_SIZE/10) * 6,((float)SCREEN_SIZE/10) * 5}, (Vector2){((float)SCREEN_SIZE/10) * 5,((float)SCREEN_SIZE/10) * 5}, (Vector2){((float)SCREEN_SIZE/10) * 5,((float)SCREEN_SIZE/10) * 6}, (Color){25,25,25,255});
            Control();
        }
        EndDrawing();
    }
    UnloadTexture(ftTexture);
    UnloadTexture(dnTexture);
    UnloadTexture(upTexture);
    UnloadTexture(dnTexture);
    UnloadTexture(rtTexture);
    UnloadTexture(lfTexture);
    UnloadShader(skyboxShader);
    UnloadModel(cube);
    CloseWindow();
    return 0;
}

void Grid()
{
    for(int i = 0; i <= SCREEN_SIZE/100; i++)
    {
        if(i == 5)
        {
            DrawLineEx((VectorPoint){.point={(float)SCREEN_SIZE/10 * i, 0}}.vector, (Vector2){(float)SCREEN_SIZE/10 * i, SCREEN_SIZE}, 3, RED);
            DrawLineEx((Vector2){0, (float)SCREEN_SIZE/10 * i}, (Vector2){SCREEN_SIZE, (float)SCREEN_SIZE/10 * i}, 3, RED);
            continue;
        }
        DrawLineEx((Vector2){(float)SCREEN_SIZE/10 * i, 0}, (Vector2){(float)SCREEN_SIZE/10 * i, SCREEN_SIZE}, 1, RED);
        DrawLineEx((Vector2){0, (float)SCREEN_SIZE/10 * i}, (Vector2){SCREEN_SIZE, (float)SCREEN_SIZE/10 * i}, 1, RED);
    }
}

void Control()
{
    if(IsKeyDown(KEY_W))
    {
        playerMovement.y -= speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_S))
    {
        playerMovement.y += speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_A))
    {
        playerMovement.x -= speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_D))
    {
        playerMovement.x += speed * GetFrameTime();
    }
}
