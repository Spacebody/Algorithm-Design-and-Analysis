#include "PreferList.h"

void initList(list p[], int rank[N][N])
{
    int i = 0,j = 0,k = 0;
    for(i = 0; i < N; ++i)
    {
        if(!(p[i].prefer = (int *)malloc(sizeof(int)*N)))
        {
            printf("No Enough Space!\n");
            exit(0);
        }
        for(j = 0; j < N; ++j)
        {
            p[i].prefer[j] = rand()%N+1; //random numbers from 1-5
            for(k = 0; k < j; ++k)
            {   //ensure that no two random numbers are the same for a person
                if(p[i].prefer[j] == p[i].prefer[k])
                {
                    --j;
                }
            }
            rank[i][p[i].prefer[j]-1] = j;
        }
        p[i].partner = 0; //set 0 as no partner, find partner from 1-5 
        p[i].state = Single; //set single at beginning
        p[i].count = -1; //count will increase 1 every time when call FineNext function, so set -1 as initial value
    }
}