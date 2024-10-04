#ifndef BASE_SORTS_H
#define BASE_SORTS_H

int SelectionSort(data arr[]);                            // done
int DoubleSelectionSort(data arr[]);                      // done
int OddEvenSort(data arr[]);                              // done
int CocktailShakerSort(data arr[]);                       // done
int RadixSortLsd(data arr[]);                             // done
int RadixCountSort(data arr[], int exp, data aux_arr[]);  // done
// The recMergeSort HAS to be called from another function at the moment.
int RecursiveMergeSort(data arr[], int l, int r);         // done
int RecursiveMergeSortCaller(data arr[]);                 // done
int BadSort(data arr[]);                                  // done
void HandleGraphic(data vect[]);


int CheckOrder(data vect[]);
// Returns 0 if it ended with no errors, 1 for user
// interrupt and -1 for a not sorted list.

#endif