#ifndef VARIABLES_CONSTANTS_H
#define VARIABLES_CONSTANTS_H

const int MAINALGX = WIDTH/2-MAINBUTTONWIDTH/2;
const int ELENUM = WIDTH/RATIO;
const int RECTWIDTH = WIDTH/ELENUM;
const int HALFWIDTH = WIDTH/2;
const int HALFHEIGHT = HEIGHT/2;

// Light theme is set as default theme at variable declaration.
extern Color backgColor;              // Background default color.
extern Color secondaryColor;          // UI default color.
extern Color sortColor;               // Sorting default color.
extern Color visualIndicatorColor;    // Array access cursor default color.
extern Color orderCheckerColor;       // Order-checker default color.

extern bool benchmark;                        // Tells the program if you're benchmarking an alg, (no graphic and bigger array).
extern int arrLen;                            // Logic lenght of the array to sort.
extern unsigned long long swaps;              // == element-swaps.
extern unsigned long long comps;              // == comparisons.
extern unsigned long long fcycles;            // == for-cycles.
extern unsigned long long marr;               // == main-array-access.
extern unsigned long long secarr;             // == secondary-array-access.

#endif