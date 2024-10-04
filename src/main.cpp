#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "raylib.h"
#include "headers/defines.h"

const int MAINALGX = WIDTH/2-MAINBUTTONWIDTH/2;
const int ELENUM = WIDTH/RATIO;
const int RECTWIDTH = WIDTH/ELENUM;
const int HALFWIDTH = WIDTH/2;
const int HALFHEIGHT = HEIGHT/2;

// Light theme is set as default theme at variable declaration.
Color backgColor = RAYWHITE;           // Background default color.
Color secondaryColor = BLACK;          // UI default color.
Color sortColor = BLACK;               // Sorting default color.
Color visualIndicatorColor = RED;      // Array access cursor default color.
Color orderCheckerColor = GREEN;       // Order-checker default color.

bool benchmark;                        // Tells the program if you're benchmarking an alg, (no graphic and bigger array).
int arrLen;                            // Logic lenght of the array to sort.
unsigned long long swaps;              // == element-swaps.
unsigned long long comps;              // == comparisons.
unsigned long long fcycles;            // == for-cycles.
unsigned long long marr;               // == main-array-access.
unsigned long long secarr;             // == secondary-array-access.

#include "headers/structs.h"
#include "headers/data_init_reset.h"
#include "headers/main_menu.h"
#include "headers/alg_menu.h"
#include "headers/settings_menu.h"

/*
    timer functioning (i have potato memory)

    struct timeval stop, start;
    gettimeofday(&start, NULL);
    do stuff
    gettimeofday(&stop, NULL);

    us/usec == microseconds == sec*10^-6
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
*/
int main()
{
    //main data initialization
    data element_list[BENCHELENUM+1], default_list[BENCHELENUM+1];
    float algtime;
    int algId;
    struct timeval stop, start;
    alg algInfo_list[ALGNUMBER];
    
    srand(time(NULL));
    InitData(default_list);
    InitAlgs(algInfo_list);
    
    ResetData(element_list, default_list, &algtime);
    
    InitWindow(WIDTH, HEIGHT, WINDOWNAME);
    SetTargetFPS(IDLEFPS);

    // entering program hyperloop, break condition is case 3.
    while(1)
    {
        benchmark = false;
        
        /*
            I'm handling both the main and algs menu in the main
            since this way i don't have to pass a huge ammount
            of variables through functions.
        */
        switch(MainMenuHandler())
        {
            case 0: break;
            case 1:
                benchmark = true;
                arrLen=BENCHELENUM;
            break;
            case 2:
                SettingsHandler();
                ResetVectColor(default_list);
                continue;
            break;
            case 3:
                CloseWindow();
                return 0;
            break;
            // pressing mouse-left out of a button hitbox.
            default:
                continue;
        }
        
        /*
            Here i'm handling the whole alg menu through one single
            function that returns the index of the sort alg inside
            the array, this way i can access all the infos about that
            sort alg easly and i don't need to make a huge switch case
            to call all the different algorythms, i instead use function
            pointers inside the "alg type" array.

            I know is quite ugly but it works well, and changing it requires
            too much time and it makes no sense to do so since its basically
            like a separated function relative to the main menu part.
        */
        algHandling:
        algId = AlgsMenuHandler(algInfo_list);
        
        /*
            If the user pressed somewhere in a non valid spot i just ignore it
            and go back to the start of the alg menu part.
        */
        if(algId > -1)
        {
            ResetData(element_list, default_list, &algtime);
            if(benchmark)
                DrawWaitSortingScreen();
            else
                SetTargetFPS(STDFPS);
            
            /*
                1) saving start point for the timer
                2) sorting the array through function pointer
                3) saving end point for the timer
            */
            gettimeofday(&start, NULL);
            algInfo_list[algId].algFunc(element_list);
            gettimeofday(&stop, NULL);
            
            // separating sec from usec and adding them together into a float.
            algtime+=stop.tv_sec - start.tv_sec;
            algtime+=(float)(stop.tv_usec - start.tv_usec) / 1000000;
            
            RecapScreen(algInfo_list[algId].algName, algtime, element_list);
        }
        else if(algId == -2)
            continue;
        else
            goto algHandling;
        
        continue;
    }
}