#include "raylib.h"

#include "headers/defines.h"
#include "headers/variables_constants.h"
#include "headers/structs.h"
#include "headers/main_menu.h"

static int CheckMainMenuCollisions();
static void DrawMainMenu();

int MainMenuHandler()
{
    int choice;
    while(!WindowShouldClose())
    {
        DrawMainMenu();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            choice = CheckMainMenuCollisions();
            if(choice >= 0)
                return choice;
       }
    }
    return -1;
}

int CheckMainMenuCollisions()
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    
    // god also forgive me for this shit
    if(mouseX > MAINALGX && mouseY > 400 && mouseX < MAINALGX+MAINBUTTONWIDTH && mouseY < 400+MAINALGHEIGHT) return 0; //normal mode
    if(mouseX > MAINALGX && mouseY > 500 && mouseX < MAINALGX+MAINBUTTONWIDTH && mouseY < 500+MAINALGHEIGHT) return 1; //benchmark mode
    if(mouseX > MAINALGX && mouseY > 600 && mouseX < MAINALGX+MAINBUTTONWIDTH && mouseY < 600+MAINALGHEIGHT) return 2; //settings
    if(mouseX > MAINALGX && mouseY > 700 && mouseX < MAINALGX+MAINBUTTONWIDTH && mouseY < 700+MAINALGHEIGHT) return 3; //exit
    return -1;
}

void DrawMainMenu()
{
    /*
        Yeeeeeeahh, even more magic values wich represent
        the coordinates on where to draw all the buttons
        and text.
    */
    BeginDrawing();

        /*
            DrawRectangle(x, y, width, height, Fade(color, fade-ammount));
            DrawText(TextFormat("Text"), x + offset-from-border, y / 2 + offset-from-border, font-size, color);
        */

        ClearBackground(backgColor);
        DrawText(TextFormat("Sorting Algorythms Visualizer"), 300, 180+MAINALGHEIGHT/2, 70, secondaryColor);
    
        DrawRectangle(MAINALGX, 400, MAINBUTTONWIDTH, MAINALGHEIGHT, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Normal Sort Algorythms"), MAINALGX+30, 380+MAINALGHEIGHT/2, 40, secondaryColor);
        
        DrawRectangle(MAINALGX, 500, MAINBUTTONWIDTH, MAINALGHEIGHT, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Benchmark Sort Algorythms"), MAINALGX+30, 480+MAINALGHEIGHT/2, 40, secondaryColor);
        
        DrawRectangle(MAINALGX, 600, MAINBUTTONWIDTH, MAINALGHEIGHT, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Settings"), MAINALGX+30, 580+MAINALGHEIGHT/2, 40, secondaryColor);
        
        DrawRectangle(MAINALGX, 700, MAINBUTTONWIDTH, MAINALGHEIGHT, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Exit Program"), MAINALGX+30, 680+MAINALGHEIGHT/2, 40, secondaryColor);
        
    EndDrawing();
}