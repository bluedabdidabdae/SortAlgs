#include "raylib.h"

#include "headers/defines.h"
#include "headers/variables_constants.h"
#include "headers/structs.h"
#include "headers/base_sorts.h"

static void DrawAlgsMenu(alg vect[]);
static int CheckAlgsMenuCollisions(alg vect[]);
static void DrawRecapScreen(char algName[][40], float algtime, int sorted);

int CheckAlgsMenuCollisions(alg vect[])
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    
    /*
        The coordinates of the buttons are in this case saved in
        an array, it makes the whole thing easier to expand
        and add more algorythms (i just have to change some things
        in the "data_init_reset.cpp" file).
    */
    for(int i=0; i<ALGNUMBER; i++)
        if(mouseX > vect[i].x && mouseY > vect[i].y && mouseX < vect[i].x+ALGWIDTH && mouseY < vect[i].y+ALGHEIGHT)
            return i;
    return -1;
}

void DrawAlgsMenu(alg vect[])
{
    BeginDrawing();
        ClearBackground(backgColor);
        for(int i=0; i<ALGNUMBER; i++)
        {
            // same as the "CheckAlgsMenuCollisions" function
            DrawRectangle(vect[i].x, vect[i].y, ALGWIDTH, ALGHEIGHT, Fade(secondaryColor, BUTTONFADEVALUE));
            DrawText(TextFormat(*vect[i].algName), vect[i].x+10, vect[i].y+10, 20, secondaryColor);
        }
    EndDrawing();
}

int AlgsMenuHandler(alg element_list[])
{
    int choice;
    while(1)
    {
        DrawAlgsMenu(element_list);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            choice = CheckAlgsMenuCollisions(element_list);
            if(choice >= 0 && choice < VALIDALGNUMBER)
            {
                return choice;
            }
        }
        else if(WindowShouldClose())
            return -2;
    }
}

void DrawRecapScreen(char algName[][40], float algtime, int sorted)
{
    BeginDrawing();
        ClearBackground(backgColor);
        
        DrawRectangle(                                         HALFWIDTH-500, HALFHEIGHT-300, 1000, 600, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat(*algName),                         HALFWIDTH-460, HALFHEIGHT-270, 70, secondaryColor);
        DrawText(TextFormat("Swaps: %lli", swaps),             HALFWIDTH-420, HALFHEIGHT-170, 30, secondaryColor);
        DrawText(TextFormat("Comparisons: %lli", comps),       HALFWIDTH-420, HALFHEIGHT-120, 30, secondaryColor);
        DrawText(TextFormat("For Cycles: %lli", fcycles),      HALFWIDTH-420, HALFHEIGHT-70, 30, secondaryColor);
        DrawText(TextFormat("Main arr acc: %lli", marr),       HALFWIDTH-420, HALFHEIGHT-20, 30, secondaryColor);
        DrawText(TextFormat("Second arr acc: %lli", secarr),   HALFWIDTH-420, HALFHEIGHT+30, 30, secondaryColor);
        DrawText(TextFormat("Alg work time: %f s", algtime),   HALFWIDTH-420, HALFHEIGHT+80, 30, secondaryColor);
        if(sorted == 0)
            DrawText(TextFormat("Sorted: True"),               HALFWIDTH-420, HALFHEIGHT+130, 30, secondaryColor);
        else
            DrawText(TextFormat("Sorted: False"),              HALFWIDTH-420, HALFHEIGHT+130, 30, secondaryColor);
        
    EndDrawing();
}

void RecapScreen(char algName[][40], float algtime, data element_list[])
{
    int sorted = CheckOrder(element_list);
    SetTargetFPS(IDLEFPS);
    while(!WindowShouldClose())
    {
        DrawRecapScreen(algName, algtime, sorted);
    }
}

void DrawWaitSortingScreen()
{
    BeginDrawing();
        ClearBackground(backgColor);

        DrawText(TextFormat("We sorting bro..."), HALFWIDTH-200, HALFHEIGHT-50, 50, secondaryColor);
    EndDrawing();
}