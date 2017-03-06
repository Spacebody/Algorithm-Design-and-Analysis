#include "Print.h"

void PrintList(list p[], char str)
{
    int i = 0, j = 0;
    printf("\t");
    if(str == 'm')
    {   //for man
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
    {  //for women
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

void PrintTable(int table[N][N])
{
    int i = 0, j = 0;
    printf("The result:\n\t");
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