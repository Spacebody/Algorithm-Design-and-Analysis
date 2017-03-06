#ifndef Headers_h_
#include "Headers.h"
#endif

//declaration
extern bool IsSingle(int state); //exam the state
extern int FindNext(int i, list p1[], int rank[N][N]); //find the next target
extern int Cmp(int i, int j, list p1[], list p2[], int table[N][N]); //compare
extern void GS(list p1[], list p2[], int table[N][N], int rank[N][N]); //GS process 