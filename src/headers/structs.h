#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct data_model{
    int value;
    Color color;
}data;

/*
    // Just an idea that i'm working on, this way
    // i can delete the "RecursiveMergeSortCaller" function.
    // The comments are in italian if you're asking.


    // L'union dovrebbe permettere di assegnare
    // i due tipi di puntatori a funzione, in
    // ogni caso la chiamerei sempre nel primo
    // modo ma se riesco a dichiarare entrambi i
    // tipi a c++ va bene e posso sfruttare l'overload
    // della funzione del merge sort (sempre in teoria).
    // Per ora il problema è che mi dice che sto
    // ridefinendo "int".

    union function{
    int (*algFunc)(data[]);             // formato normale
    int (*algFunc)(data[], int, int);   // formato per il merge-sort
    };
    typedef struct alg_model{
        int x;                          // posizione x del bottone
        int y;                          // posizione y del bottone
        char algName[ALGNUMBER][40];    // nome dell'algoritmo
        union function;
    }alg;
*/

typedef struct alg_model{
    int x;                          // Button x position.
    int y;                          // Button y position.
    char algName[ALGNUMBER][40];    // Algorythm name.
    int (*algFunc)(data[]);         // Algorythm function address.
}alg;

#endif