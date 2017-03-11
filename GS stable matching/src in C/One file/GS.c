//GS stable matching
//
//by Spacebody

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#define N 5
#define Succeed 1
#define Rejected -1
#define Changed -2

typedef struct people
{
    int *prefer;
    int state;
}list;

void initList(list p[]);
void PirntList(list p[], char str);
bool IsSingle(int state);
void GS(list p1[], list p2[], int table[N][N]);
void PrintTable(int table[N][N]);
int FindNext(int i, list p1[], int table[N][N]);
int Cmp(int i, int j, list p1[i], list p2[j], int table[N][N]);

int main(void)
{
    list ml[N];
    list wl[N];
    srand((unsigned)(time(NULL)));
    
    initList(ml);
    printf("Men preference list:\n");
    PirntList(ml, 'm');
    
    initList(wl);
    printf("Women preference list:\n");
    PirntList(wl, 'w');
    
    int i = 0;
    for(i = 0; i<N;++i)
    {
        printf("%d\t", ml[i].state);
    }
    printf("\n");
    for(i = 0; i<N;++i)
    {
        printf("%d\t", wl[i].state);
    }
    printf("\n");
    
    int MatchTable[N][N] = {0};
    GS(ml, wl, MatchTable);
    PrintTable(MatchTable);
    
    for(i = 0; i< N;++i)
    {
        printf("%d\t", ml[i].state);
    }
    printf("\n");
    for(i = 0; i<N;++i)
    {
        printf("%d\t", wl[i].state);
    }
    printf("\n");
    return 0;
}


void initList(list p[])
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
            p[i].prefer[j] = rand()%N+1;
            for(k = 0; k < j; ++k)
            {
                if(p[i].prefer[j] == p[i].prefer[k])
                {
                    --j;
                }
            }
        }
        p[i].state = 0;
    }
}

void PirntList(list p[], char str)
{
    int i = 0, j = 0;
    printf("\t");
    if(str == 'm')
    {
        for(i = 0; i < N; ++i)
        {
            printf("w%d\t", i+1);
        }
        printf("\n");
        for(i = 0; i< N; ++i)
        {
            printf("m%d: ",i+1);
            for(j = 0; j< N; ++j)
            {
                printf("%d\t",p[i].prefer[j]);
            }
            printf("\n");
        }
    }
    else if(str == 'w')
    {
        for(i = 0; i < N; ++i)
        {
            printf("m%d\t", i+1);
        }
        printf("\n");
        for(i = 0; i< N; ++i)
        {
            printf("w%d: ",i+1);
            for(j = 0; j< N; ++j)
            {
                printf("%d\t",p[i].prefer[j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Error\n");
        exit(0);
    }
}

bool IsSingle(int state)
{
    return state == 0;
}

void GS(list p1[], list p2[], int table[N][N])
{
    int i = 0, j = 0, count = 0;
    for(i = 0; (i %= N) < N ; ++i)
    {
        while(IsSingle(p1[i].state))
        {
            j = FindNext(i, p1, table);
            if(Cmp(i, j, p1, p2, table) == Succeed )
            {
                ++count;
                break;
            }
            else if(Cmp(i, j, p1, p2, table) == Rejected)
            {
                continue;
            }
            else if(Cmp(i, j, p1, p2, table) == Changed)
            {
                break;
            }
        } 
        if(count == N)
        {
            break;
        }
    }
    printf("i is %d\n", i);
    printf("count is %d\n", count);
    
}

int FindNext(int i, list p1[], int table[N][N])
{
    int j = 0, request = N+1, k = 0;
    j = k;
    for(k = 0; k<N; ++k)
    {
        if((table[i][k] != Rejected) && (p1[i].prefer[k] < request))
        {
            request = p1[i].prefer[k];
            j = k;
        }
    }
    //printf("j is %d\t", j);
    return j;
}



int Cmp(int i, int j, list p1[], list p2[], int table[N][N])
{
    if(IsSingle(p2[j].state))
    {
        p1[i].state = j+1;
        p2[j].state = i+1;
        table[i][j] = i+1;
        return Succeed;
    }
    else if(!IsSingle(p2[j].state) && p2[j].prefer[i] > p2[j].prefer[p2[j].state-1])
    {
        p1[i].state = 0;
        table[i][j] = Rejected;
        return Rejected;
    }
    else
    {
        //p2[j].state > 0 && p2[j].prefer[i] < p2[j].state
        p1[i].state = j+1;
        table[p2[j].state-1][j] = Changed;
        p1[p2[j].state-1].state = 0;
        p2[j].state = i+1;
        table[i][j] = i+1;
        return Changed;
    }
}

void PrintTable(int table[N][N])
{
    int i = 0, j = 0;
    printf("The result was:\n\t");
    for(i = 0; i < N; ++i)
    {
        printf("w%d\t", i+1);
    }
    printf("\n");
    for(i = 0; i < N; ++i)
    {
        printf("m%d: ", i+1);
        for(j = 0; j < N; ++j)
        {
            printf("%d\t",table[i][j]);
        }
        printf("\n");
    }
}

