/*******************************************************************************************
*
*   Physac - Hello World
*
*   NOTE: Physac requires multi-threading, when InitPhysics() a second thread is created to manage physics calculations.
*   The file pthreadGC2.dll is required to run the program; you can find it in 'src\external'
*
*   Copyright (c) 2016 Victor Fisac
*
********************************************************************************************/

#define PHYSAC_IMPLEMENTATION
#include "physac.h"
#include "stdio.h"

#define     FORCE       100
#define     TORQUE      10000

int main()
{
    remove("physac_log.txt");
    
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [physac] - demo");
    SetTargetFPS(60);
    
    InitPhysics((Vector2){ 0.0f, 0 });     // TODO: check if real world gravity value gives good results
    
    PhysicsBody A = CreatePhysicsBodyCircle((Vector2){ screenWidth/2, screenHeight/2 }, 2, 30);
    PhysicsBody B = CreatePhysicsBodyCircle((Vector2){ screenWidth/2 + 100, screenHeight/2 - 70 }, 2, 30);
    PhysicsBody C = CreatePhysicsBodyPolygon((Vector2){ screenWidth/2 + 300, screenHeight/2 + 100 }, 10);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------        
        if (IsKeyPressed('F')) frameStepping = !frameStepping;
        if (IsKeyDown(' ')) canStep = true;
        
        if (IsKeyDown('D')) B->force.x += FORCE;
        else if (IsKeyDown('A')) B->force.x -= FORCE;
        
        if (IsKeyDown('S')) B->force.y += FORCE;
        else if (IsKeyDown('W')) B->force.y -= FORCE;
        
        if (IsKeyDown('T')) B->torque += TORQUE;        
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            DrawPhysicsBodies();
            
            DrawPhysicsContacts();
            
            DrawPhysicsInfo();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    ClosePhysics();       // Unitialize physics
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}