#include "raylib.h"

#include "headers/defines.h"
#include "headers/variables_constants.h"
#include "headers/structs.h"
#include "headers/settings_menu.h"

static void DrawSettings();
static int CheckSettingsMenuCollisions();

/*
    At the moment the themes are hard coded in this
    function, i'm leaving them in here and maybe
    adding more in the future, i also plan to
    implement a custom theme function with
    a "userSettings.json" file.
*/
void SettingsHandler()
{
    while(!WindowShouldClose())
    {
        DrawSettings();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            switch(CheckSettingsMenuCollisions())
            {
                // light theme
                case 1:
                    backgColor = RAYWHITE;
                    secondaryColor = BLACK;
                    sortColor = BLACK;
                    visualIndicatorColor = RED;
                    orderCheckerColor = GREEN;
                break;
                // dark theme
                case 2:
                    backgColor = BLACK;
                    secondaryColor = RAYWHITE;
                    sortColor = RAYWHITE;
                    visualIndicatorColor = RED;
                    orderCheckerColor = GREEN;
                break;
                // blood theme
                case 3:
                    backgColor = BLACK;
                    secondaryColor = RED;
                    sortColor = RED;
                    visualIndicatorColor = BLUE;
                    orderCheckerColor = MAROON;
                break;
                // hack theme
                case 4:
                    backgColor = BLACK;
                    secondaryColor = GREEN;
                    sortColor = GREEN;
                    visualIndicatorColor = RED;
                    orderCheckerColor = DARKGREEN;
                break;
                // ocean theme
                case 5:
                    backgColor = RAYWHITE;
                    secondaryColor = BLUE;
                    sortColor = BLUE;
                    visualIndicatorColor = RED;
                    orderCheckerColor = DARKBLUE;
                break;
                // donut theme
                case 6:
                    backgColor = RAYWHITE;
                    secondaryColor = PINK;
                    sortColor = PINK;
                    visualIndicatorColor = BLUE;
                    orderCheckerColor = PURPLE;
                break;
                
                default: continue;
            }
        }
    }
}

/*
    I'm just giving up, i don't even remember the logic
    behind these values, i swear i'm going to fix this 
    soon or later (i hope)
*/
int CheckSettingsMenuCollisions()
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if(mouseY > 210 && mouseY < 260)
    {
        if(mouseX > 600  && mouseX < 730)   return 1;
        if(mouseX > 750  && mouseX < 880)   return 2;
        if(mouseX > 900  && mouseX < 1030)  return 3;
        if(mouseX > 1050 && mouseX < 1180)  return 4;
        if(mouseX > 1200 && mouseX < 1330)  return 5;
        if(mouseX > 1350 && mouseX < 1580)  return 6;
    }
    return 0;
}

// see last comment
void DrawSettings()
{
    BeginDrawing();
        ClearBackground(backgColor);
        DrawText(TextFormat("Settings"),              120, 100, 60, secondaryColor);
    
        DrawRectangle(                                100, 210, 400, 50, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("- Themes"),              120, 220, 30, secondaryColor);
        
        DrawRectangle(                                600, 210, 130,  50, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Light"),                 620, 220, 30,  secondaryColor);
        DrawRectangle(                                750, 210, 130,  50, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Dark"),                  770, 220, 30,  secondaryColor);
        DrawRectangle(                                900, 210, 130,  50, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Blood"),                 920, 220, 30,  secondaryColor);
        DrawRectangle(                                1050, 210, 130, 50, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Hack"),                  1070, 220, 30, secondaryColor);
        DrawRectangle(                                1200, 210, 130, 50, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Ocean"),                 1220, 220, 30, secondaryColor);
        DrawRectangle(                                1350, 210, 130, 50, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Donut"),                 1370, 220, 30, secondaryColor);
    EndDrawing();
}