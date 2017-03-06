

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> //use system time to get a seed 


#ifndef Headers_H_
#define Headers_H_

#define N 5  //the number of the people
#define Succeed 1 //if matched
#define Rejected -1 //if rejected 
#define Changed -2 //if seized others wife
#define Matched 1 //state of the person, matched 
#define Single 0 //if single 

typedef struct people
{
    int *prefer; //preference list 
    int partner; //his/her matched person
    int state; //matched or single 
    int count; //count for choose the target
}list;

#endif 