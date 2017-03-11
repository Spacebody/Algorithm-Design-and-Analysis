//GS stable matching
//
//Based on standard C99
//
//by 11510506 郑艺林

/*
 *some headers are included in Headers.h which is uesd by others .c files.
 *Also the definition of struct 
 */
 
#include "GS.c"  //the c file of the GS function
#include "PreferList.c" //the file of the initialization funtion 
#include "Print.c"  //the file contains some print function

static list ml[N]; //struct array of men
static list wl[N]; // struct array of women
static int MenRank[N][N] = {0}; //rank of men
static int WomenRank[N][N] = {0}; //rank of women
static int MatchTable[N][N] = {0}; //the record of the process

int main(void)
{
    srand((unsigned)(time(NULL))); //random a seed
  
    initList(ml, WomenRank); //initialize the preference list
    printf("Men preference list:\n");
    PrintList(ml, 'm'); //print to see 
    
    initList(wl, MenRank);
    printf("Women preference list:\n");
    PrintList(wl, 'w');
    
	GS(ml, wl, MatchTable, WomenRank); //GS matching process
    
    PrintTable(MatchTable); //print the result

    return 0;
}