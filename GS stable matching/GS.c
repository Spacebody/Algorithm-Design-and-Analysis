#include "GS.h"

bool IsSingle(int state)
{
    return state == Single; //if single, return true
}


int FindNext(int i, list p1[], int rank[N][N])
{
	//firstly increase count to get the inedx of the best love one
	//find the NO in the rank table 
    return rank[i][++(p1[i].count)]; 
}

int Cmp(int i, int j, list p1[], list p2[], int table[N][N])
{
    if(IsSingle(p2[j].state))
    {   //if the target woman is single, naturally match them
        p1[i].state = Matched; //change the state
        p1[i].partner = j+1;  //record the partner 
        p2[j].state = Matched; 
        p2[j].partner = i+1;
        table[i][j] = i+1; //recored in the result
        return Succeed;
    }
    else
    {
    	//if target woman had been matched, then compare to decide whether to change
    	if(p2[j].prefer[p2[j].partner-1] < p2[j].prefer[i])
    	{   //so weak, be rejected
        	table[i][j] = Rejected;
        	return Rejected;
    	}
    	else
    	{   //defeat the fucking man and seize the woman, then that man will be single again 
	        p1[i].partner = j+1;
	        p1[(p2[j].partner)-1].state = Single;  //use the record in the woman struct to locate poor man
    	    p1[(p2[j].partner)-1].partner = 0;
    	    table[(p2[j].partner)-1][j] = Changed;//record the change situation
	        p2[j].partner = i+1; 
    	    table[i][j] = i+1; //record the match result
	        return Changed;
    	}
    }
}

void GS(list p1[], list p2[], int table[N][N], int rank[N][N])
{
	//p1 means wan, p2 means woman
    int i = 0, j = 0, count = 0; //count is to record the number of matched people 
    for(i = 0; (i %= N) < N ; ++i)
    {    //loop from 0-4 again and again
        while(IsSingle(p1[i].state))
        {   //if find a single man
            j = FindNext(i, p1, rank); //find his target
            if(Cmp(i, j, p1, p2, table) == Succeed )
            {   
                ++count; //increase the count if succceed 
                break;
            }
            else if(Cmp(i, j, p1, p2, table) == Rejected)
            {
                continue; //no change 
            }
            else if(Cmp(i, j, p1, p2, table) == Changed)
            {
            	p1[i].state = Matched; //this fucking code will NOT execute if put in Cmp funtion, I don't know why.
                break;
            }
        }
        if(count == N)
        {
        	//exam the count, if all person have been matched, break to end the loop
            break;
        }
    }
}