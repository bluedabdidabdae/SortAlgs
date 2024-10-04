#include <string.h>
#include <stdlib.h>

#include "raylib.h"

#include "headers/defines.h"
#include "headers/variables_constants.h"
#include "headers/structs.h"
#include "headers/data_init_reset.h"
#include "headers/base_sorts.h"


void ResetVectColor(data vect[])
{
    for(int i=0; i<ELENUM; i++)
        vect[i].color=sortColor;
}

/*
    Here i'm initializing the list of available
    algorythms wich i'm using in the main function
    by generating the coorinates of all the buttons
    and inserting the function pointers while also
    inserting the name of the relative algorythm.
*/
void InitAlgs(alg vect[])
{
    int algRows = ALGNUMBER;
    int algCols = 1;
    int nOfAlgs = ALGNUMBER;
    
    for(int i=0; i<ALGNUMBER; i++)
        strcpy(*vect[i].algName, "NULL");
    
    for(int i=1; i<=algCols && nOfAlgs > 0; i++)
    {
        for(int j=1; j<=algRows && nOfAlgs > 0; j++)
        {
            vect[j-1].x=50*i+ALGWIDTH;
            vect[j-1].y=50*j+ALGHEIGHT;
            nOfAlgs--;
        }
    }
    
    strcpy(*vect[0].algName, "Recursive mergesort\0");
    vect[0].algFunc = RecursiveMergeSortCaller;
    strcpy(*vect[1].algName, "Lsd radix sort\0");
    vect[1].algFunc = RadixSortLsd;
    strcpy(*vect[2].algName, "Odd even sort\0");
    vect[2].algFunc = OddEvenSort;
    strcpy(*vect[3].algName, "Cocktail shaker sort\0");
    vect[3].algFunc = CocktailShakerSort;
    strcpy(*vect[4].algName, "Selection sort\0");
    vect[4].algFunc = SelectionSort;
    strcpy(*vect[5].algName, "Double selection sort\0");
    vect[5].algFunc = DoubleSelectionSort;
    strcpy(*vect[6].algName, "Bad sort\0");
    vect[6].algFunc = BadSort;
    
}

/*
    Populating the default list to order
*/
void InitData(data vect[])
{
    for(int i=0; i<ELENUM; i++)
    {
        vect[i].value=rand()%(MAX-MIN)+MIN;
        vect[i].color=sortColor;
    }
    
    for(int i=ELENUM; i<BENCHELENUM; i++)
    {
        vect[i].value=rand()%(BENCHELENUM-MIN)+MIN;
        vect[i].color=sortColor;
    }
}

/*
    Copying the default array into the array that
    the program sorts, this way you can always test
    the algs with the same array while also resetting
    the counters.
    
    TODO: make a function that re-initializes
          the default array so you don't need
          to restart the program
*/
void ResetData(data vect[], data vect2[], float *algtime)
{
    for(int i=0; i<arrLen; i++)
        vect[i]=vect2[i];
    
    arrLen=ELENUM;
    *algtime=0;
    fcycles=0;
    swaps=0;
    comps=0;
    marr=0;
    secarr=0;
}
