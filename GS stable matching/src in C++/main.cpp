/**
 * main
 * use object
 * use multiple data structures
 *
 * for large scale matching, set data manually
 *
 * By Spacebody
 */

#include <iostream>
#include "Human.cpp" //include the class file
#include <vector> //use vector to store objects 
#include <queue> //use queue to store matching objects

#define N 5
#define None "\0" //define the no partner as None

typedef vector<Human> Person; //Men and Women
typedef queue<int> MatchQueue; //stroe the index of object in the vector
typedef map<string, int> NametoOrder; //find index in the vector according to name

//definition of function
void InitList(string Men[], string Women[], \
			  int MenList[][N], int WomenList[][N], \
			  Person &MenSet, Person &WomenSet); //initialize list

void GSMatching(Person &MenSet, Person &WomenSet, MatchQueue &M, \
				NametoOrder &MenOrder, NametoOrder &WomenOrder); //GS match function

void PrintResult(Person &toMatch); //print result


int main(void)
{
    //test data
	string Men[] = {"Aaron", "Bill", "Christ", "Duke", "Jay"};
	string Women[] = {"Abby", "Estelle", "Iris", "Alice", "Linda"};

	//tow arrays for generating the preference
	int MenList[][N] = {1,4,3,0,2,
						1,2,3,0,4,
						3,4,2,0,1,
						4,1,0,3,2,
						2,0,1,3,4};
	
	int WomenList[][N] = {0,2,4,1,3,
						  0,1,2,3,4,
						  2,4,1,3,0,
						  3,1,4,0,2,
						  2,4,3,0,1,};
	
	Person MenSet;
	Person WomenSet;
	NametoOrder MenOrder, WomenOrder;
	MatchQueue M;

	//push objects in to vector
	for(int i = 0; i< N;++i)
	{
		MenSet.push_back(Human());
		WomenSet.push_back(Human());
		MenOrder.insert(pair<string, int>(Men[i], i));
		WomenOrder.insert(pair<string, int>(Women[i], i));
	}

	//match process
	InitList(Men, Women, MenList, WomenList, MenSet, WomenSet);
	GSMatching(MenSet, WomenSet, M, MenOrder, WomenOrder);
	PrintResult(MenSet);

	//matched over, free memory
	for(int i = 0; i< N;++i)
	{
		MenSet.pop_back();
		WomenSet.pop_back();
		MenOrder.erase(Men[i]);
		WomenOrder.erase(Women[i]);
	}
	return 0; 
}


void InitList(string Men[], string Women[], int MenList[][N], \
			  int WomenList[][N], Person &MenSet, Person &WomenSet)
{
	for(int i = 0; i< N;++i)
	{
		MenSet[i].setName(Men[i]); //set name
		MenSet[i].setState(true); //set initial state
		MenSet[i].setCounter(); //set conuter 
		MenSet[i].setPartner(None); //no partner at beginning

		WomenSet[i].setName(Women[i]);
		WomenSet[i].setState(true);
		WomenSet[i].setCounter();
		WomenSet[i].setPartner(None);
		for(int j = 0; j < N; ++j)
		{
			MenSet[i].initList(j, Women[MenList[i][j]]); //create preference list

			WomenSet[i].initList(j, Men[WomenList[i][j]]);
		}
	}
}

void GSMatching(Person &MenSet, Person &WomenSet, MatchQueue &M, \
				NametoOrder &MenOrder, NametoOrder &WomenOrder)
{	
	cout<<"Matching process:"<<endl;
	for(int i = 0; i< N; ++i)
	{
		M.push(i); //push index
	}
	while(!M.empty()) 
	{ //loop if queue is not empty

		int i = M.front(); //get the front element
		string targetPartner = MenSet[i].FindNext(); //find target name
		int j = WomenOrder[targetPartner]; //just to simplify code
		cout<<MenSet[i].getName()+" chooses "+targetPartner+"." <<endl;
		if(WomenSet[j].getState())
		{   //if woman is single
			MenSet[i].setState(false); //change state
			MenSet[i].setPartner(targetPartner); //record the partner name 
			WomenSet[j].setState(false);
			WomenSet[j].setPartner(MenSet[i].getName());
			cout<<MenSet[i].getName()+" and "+targetPartner+" are dating."<<endl<<endl; 
			M.pop(); //pop out the element
		}
		else
		{
			if(MenSet[i].breakUp(WomenSet[j].NametoRank(MenSet[i].getName()), \
				WomenSet[j].NametoRank(WomenSet[j].getPartner())))
			{	//if breaking up 
				int k = MenOrder[WomenSet[j].getPartner()];
				MenSet[k].setState(false);
				MenSet[k].setPartner(None);
				M.push(k); //push the poor man into the queue
				MenSet[i].setState(false);
				MenSet[i].setPartner(targetPartner); 
				M.pop(); //pop out the winner 
				
				cout<<MenSet[i].getName()+" and "+targetPartner+" are dating.\n"+\
				WomenSet[j].getPartner()+" is single again."<<endl<<endl;
				
				WomenSet[j].setPartner(MenSet[i].getName());
			}
			else
			{	
				cout<<MenSet[i].getName()+" is rejected "+targetPartner+" then remains single."<<endl<<endl;
				M.push(i);//push in if not succeed
				M.pop(); //pop out for next one to be matched
			}
		}
	}
	cout<<"Matching Finished."<<endl;
}

void PrintResult(Person &toMatch)
{
	cout<<"Result:"<<endl;
	for(int i = 0; i < N; ++i)
	{
		cout<<endl<<toMatch[i].getName()+" matches "+toMatch[i].getPartner()<<endl;
	}
}
