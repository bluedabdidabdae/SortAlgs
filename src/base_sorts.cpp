#include "raylib.h"

#include "headers/defines.h"
#include "headers/variables_constants.h"
#include "headers/structs.h"
#include "headers/base_sorts.h"

static int MergeArrays(data arr[], int l, int m, int r);         // done
static void Swap(data *ele1, data *ele2);                        // done
static int GetMax(data arr[]);                                   // done

/*
    All the algorythms in here are known sorting
    algs, if you need documentation about them
    you can find it online (i'm not explaining
    how every alg works).
    If i added some strange stuff i commented
    it (i hope).
*/

int BadSort(data arr[]) // non e' colpa mia sono stato costretto
{
    for (int i = 0; i < arrLen; i++){
        fcycles++; // for cycle
        for (int ii = 0; ii < arrLen-1; ii++){
            fcycles++; // for cycle
            marr+=2; // double main array access
            comps++; // comparazione dell'if
            if (arr[ii].value > arr[ii+1].value){
                swaps++; //  swapping 2 elements
                Swap(&arr[ii], &arr[ii+1]);
                ii = 0;
                if(WindowShouldClose())
                    return 1;
                if(!benchmark)
                    HandleGraphic(arr);
            }
        }
    }
    return 0;
}

int RecursiveMergeSort(data arr[], int l = 0, int r = arrLen)
{
    comps++; // if comparison
    if (l < r) {
        int m = l + (r - l) / 2;
 
        if(RecursiveMergeSort(arr, l, m) == 1)
            return 1;
        if(RecursiveMergeSort(arr, m + 1, r) == 1)
            return 1;
        if(MergeArrays(arr, l, m, r) == 1)
            return 1;
    }
    return 0;
}

/*
    I must call it this way for the
    moment, i'm working on a way to
    improve it.
*/
int RecursiveMergeSortCaller(data arr[])
{
    return RecursiveMergeSort(arr, 0, arrLen);
}

int RadixSortLsd(data arr[])
{
    int m = GetMax(arr);
    data outputarr[arrLen+1];
    
    for(int tmp=0; tmp<arrLen; tmp++)
    {
        outputarr[tmp].value=arr[tmp].value;
        outputarr[tmp].color=arr[tmp].color;
    }

    if(WindowShouldClose())
        return 1;
    if(!benchmark)
        HandleGraphic(outputarr);

    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        fcycles++; // for cycle
        if(RadixCountSort(arr, exp, outputarr) == 1)
            return 1;
    }
    return 0;
}

int RadixCountSort(data arr[], int exp, data aux_arr[])
{
    int count[10];
    int i;

    for(i=0;i<10;i++)
    {
        secarr++; // secondary array access
        fcycles++; // for cycle
        count[i]=0;
    }

    for (i = 0; i < arrLen; i++)
    {
        secarr++; // secondary array access
        fcycles++; // for cycle
        count[(arr[i].value / exp) % 10]++;
    }

    for (i = 1; i < 10; i++)
    {
        secarr++; // secondary array access
        fcycles++; // for cycle
        count[i] += count[i - 1];
    }

    for (i = arrLen - 1; i >= 0; i--) {
        fcycles++; // for cycle
        marr++; // main array access
        secarr++; // secondary array access
        aux_arr[count[(arr[i].value / exp) % 10] - 1].value = arr[i].value;
        count[(arr[i].value / exp) % 10]--;
    }

    for (i = 0; i < arrLen; i++)
    {
        if(WindowShouldClose())
            return 1;
        if(!benchmark)
        {
            arr[i].color=visualIndicatorColor;
            HandleGraphic(arr);
            arr[i].color=sortColor;
        }
        fcycles++; // for cycle
        marr++; // main array access
        secarr++; // secondary array access
        arr[i].value = aux_arr[i].value;
    }
    return 0;
}

int OddEvenSort(data arr[])
{
    bool sorted=false;
    while(!sorted)
    {
        sorted=true;
        for(int c=1; c<arrLen-1; c+=2)
        {
            marr+=2; // double main array access
            comps++; // if comparison
            if(arr[c].value>arr[c+1].value)
            {
                marr+=2; // double main array access
                swaps++; // swapping 2 elements
                Swap(&arr[c], &arr[c+1]);
                if(WindowShouldClose())
                    return 1;
                sorted=false;
            }
            fcycles++; // for cycle
            
        }
        
        if(!benchmark)
            HandleGraphic(arr);
        
        for(int c=0; c<arrLen-1; c+=2)
        {
            marr+=2; // double main array access
            comps++; // if comparison
            if(arr[c].value>arr[c+1].value)
            {
                marr+=2; // double main array access
                swaps++; // swapping 2 elements
                Swap(&arr[c], &arr[c+1]);
                if(WindowShouldClose())
                    return 1;
                sorted=false;
            }
            fcycles++; // for cycle
        }
        
        if(!benchmark)
            HandleGraphic(arr);
    }
    return 0;
}

int CocktailShakerSort(data arr[])
{
    int c;
    bool sorted=false;
    for(int i=arrLen; i>arrLen/2&&!sorted; i--)
    {
        sorted=true;
        for(c=arrLen-i; c<i; c++)
        {
            marr+=2; // double main array access
            comps++; // comparazione dell'if
            if(arr[c].value>arr[c+1].value)
            {
                marr+=2; // double main array access
                swaps++; //  swapping 2 elements
                Swap(&arr[c], &arr[c+1]);
                sorted=false;
            }
            if(WindowShouldClose())
                return 1;
            fcycles++; // for cycle
        }
        if(!benchmark)
            HandleGraphic(arr);
        for(c=c; c>=arrLen-i; c--)
        {
            marr+=2; // double main array access
            comps++; // comparazione dell'if
            if(arr[c].value>arr[c+1].value)
            {
                marr+=2; // double main array access
                swaps++; //  swapping 2 elements
                Swap(&arr[c], &arr[c+1]);
                sorted=false;
            }
            if(WindowShouldClose())
                return 1;
            fcycles++; // for cycle
        }
        if(!benchmark)
            HandleGraphic(arr);
        fcycles++; // for cycle
    }
    return 0;
}

int DoubleSelectionSort(data arr[])
{
    int max, min;
    for(int c=arrLen; c>arrLen/2; c--){
        min=c-1;
        max=0;
        for(int i=arrLen-c; i<c; i++)
        {
            marr+=2; // double main array access
            comps++; // comparazione dell'if
            if(arr[i].value>arr[max].value)
                max=i;
            fcycles++; // for cycle
        }
        
        marr+=2; // double main array access
        swaps++; //  swapping 2 elements
        Swap(&arr[max], &arr[c-1]);
        
        if(WindowShouldClose())
            return 1;
        if(!benchmark)
        {
            arr[max].color=visualIndicatorColor;
            arr[c-1].color=visualIndicatorColor;
            HandleGraphic(arr);
            arr[max].color=sortColor;
            arr[c-1].color=sortColor;
        }
        
        for(int i=arrLen-c; i<c; i++)
        {
            marr+=2; // double main array access
            comps++; // comparazione dell'if
            if(arr[i].value<arr[min].value)
                min=i;
            fcycles++; // for cycle
        }
        
        marr+=2; // double main array access
        swaps++; //  swapping 2 elements
        Swap(&arr[min], &arr[arrLen-c]);
        
        if(WindowShouldClose())
            return 1;
        if(!benchmark)
        {
            arr[min].color=visualIndicatorColor;
            arr[arrLen-c].color=visualIndicatorColor;
            HandleGraphic(arr);
            arr[min].color=sortColor;
            arr[arrLen-c].color=sortColor;
        }   
        fcycles++; // for cycle
    }
    return 0;
}

int SelectionSort(data arr[])
{
    int max;
    for(int c=arrLen; c>0; c--){
        max=0;
        for(int i=1; i<c; i++)
        {
            marr+=2; // double main array access
            comps++; // comparazione dell'if
            if(arr[i].value>arr[max].value)
                max=i;
            fcycles++; // for cycle
        }
        
        marr+=2; // double main array access
        swaps++; //  swapping 2 elements
        Swap(&arr[max], &arr[c-1]);
        
        if(WindowShouldClose())
            return 1;
        if(!benchmark)
        {
            arr[max].color=visualIndicatorColor;
            HandleGraphic(arr);
            arr[max].color=sortColor;
        }
        fcycles++; // for cycle
    }
    return 0;
}

int MergeArrays(data arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    data L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
    {
        fcycles++; // for cycle
        secarr++; // secondary array access
        marr++; // main array access
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        fcycles++; // for cycle
        secarr++; // secondary array access
        marr++; // main array access
        R[j] = arr[m + 1 + j];
    }
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        fcycles++; // for cycle
        secarr++; // secondary array access
        marr++; // main array access
        comps++; // if comparison
        if (L[i].value <= R[j].value) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        if(WindowShouldClose())
            return 1;
        if(!benchmark)
        {
            arr[k].color=visualIndicatorColor;
            HandleGraphic(arr);
            arr[k].color=sortColor;
        }
        k++;
    }
 
    while (i < n1) {
        fcycles++; // for cycle
        secarr++; // secondary array access
        marr++; // main array access
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        fcycles++; // for cycle
        secarr++; // secondary array access
        marr++; // main array access
        arr[k] = R[j];
        j++;
        k++;
    }
    return 0;
}

void Swap(data *ele1, data *ele2)
{
    data tmp = *ele1;
    *ele1=*ele2;
    *ele2=tmp;
}

int GetMax(data arr[])
{
    int max = arr[0].value;
    for (int i = 1; i < arrLen; i++)
        if (arr[i].value > max)
            max = arr[i].value;
    return max;
}

int CheckOrder(data vect[])
{
    SetTargetFPS(MAXRAYLIBFPS);
    for(int i=0; i<arrLen-1; i++)
    {
        if(vect[i].value <= vect[i+1].value)
            vect[i].color = orderCheckerColor;
        else
            return -1;
        if(WindowShouldClose()) // This way i don't lock the user in this phase of the program
            return 1;
        if(!benchmark)
            HandleGraphic(vect);
    }
    return 0;
}

void HandleGraphic(data vect[])
{
    int offset = 0;
    BeginDrawing();
    
        ClearBackground(backgColor);
        for(int i=0; i<ELENUM; i++)
        {
            /*
                Drawing all the values while in normal
                mode (the first "width" values are "0 < x < height")
            */
            DrawRectangle(offset, HEIGHT-vect[i].value, RECTWIDTH, vect[i].value, vect[i].color);
            offset+=RECTWIDTH;
        }

        /*
            Yup, lot of magic values aka coordinates, anyways
            i'm printing all the parameters of the current sort
            wich is being run
        */
     // DrawText(TextFormat("Integer value: %d", val), x, y, size, color);
        DrawRectangle(0, 0, 150, 95, Fade(secondaryColor, BUTTONFADEVALUE));
        DrawText(TextFormat("Swaps: %lli", swaps), 10, 10, 10, secondaryColor);
        DrawText(TextFormat("Comparisons: %lli", comps), 10, 25, 10, secondaryColor);
        DrawText(TextFormat("For Cycles: %lli", fcycles), 10, 40, 10, secondaryColor);
        DrawText(TextFormat("Main arr acc: %lli", marr), 10, 55, 10, secondaryColor);
        DrawText(TextFormat("Second arr acc: %lli", secarr), 10, 70, 10, secondaryColor);
        
    EndDrawing();
}