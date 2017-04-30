#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef struct UserRecord
{
	string Name; //users' name
	pair<int, int> Songs[10]; //songs record
	int Rank[10];  //songs rank
	int Inversion; //inversion number
}User;
bool compSongsbyNum(const pair<int, int> &pair1, const pair<int, int> &pair2)
{    //for sort by times of listenning
    return pair1.first > pair2.first;
}
bool compSongsbyIndex(const pair<int, int> &pair1, const pair<int, int> &pair2)
{	//for sort by index in array
    return pair1.second < pair2.second;
}
bool compInversion(const User &user1,const User &user2)
{	//sort by inversion value
    return user1.Inversion < user2.Inversion;
}

int Sort_Count(int A[], int N); //driver function
int Sort_and_Count(int A[], int auxL[], int left, int right); //sort array and count inversion 
int Merge_and_Count(int A[], int auxL[], int leftPos, int rightPos, int rightEnd); //merge and count
void Count_and_Print(string infile); //execute in file, output to file
void findRank(pair<int, int> Songs[], int Rank[]); //find rank according to numbers

int Sort_Count(int A[], int N)
{
	int *auxL;
	auxL = new int[N];
	int rCount;
	if(auxL != NULL)
	{	//clone the array to auxL
		for(int i = 0;i<N;++i)
		{
			auxL[i] = A[i];
		}	
		rCount = Sort_and_Count(A, auxL, 0, N-1);
		delete(auxL); //delete temp array
	}
	else
	{
		cerr<<"Out of Space"<<endl;
		exit(1);
	}
	return rCount;
} 

int Sort_and_Count(int A[], int auxL[], int left, int right)
{
	int rLeft, rRight, r = 0;
	if(left == right)
	{
		return 0;
	}
	int mid = left + (right-left)/2;
	rLeft = Sort_and_Count(A, auxL, left, mid); //segment A
	rRight = Sort_and_Count(A, auxL, mid+1, right);//segment B
	if(auxL[mid] <= auxL[mid+1])
	{     //Optimization strategy
		for(int i = left;i<=right;++i)
		{
			A[i] = auxL[i];
		}
	}
	else
	{	//Optimization strategy
		r = Merge_and_Count(A, auxL, left, mid+1, right);
	}
	return rLeft+rRight+r;
}

int Merge_and_Count(int auxL[], int A[], int leftPos, int rightPos, int rightEnd)
{
	int r = 0, leftEnd = rightPos-1, N = rightEnd-leftPos + 1, tmpPos = leftPos;
	while(leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if(auxL[leftPos] <= auxL[rightPos])
		{  
			A[tmpPos++] = auxL[leftPos++]; 
		}
		else
		{
			A[tmpPos++] = auxL[rightPos++];
			r += leftEnd - leftPos + 1;
		}
	}
	while(leftPos <= leftEnd)
	{
		A[tmpPos++] = auxL[leftPos++];
	}
	while(rightPos <= rightEnd)
	{
		A[tmpPos++] = auxL[rightPos++]; 
	}
	for(int i = 0;i < N; ++i, --rightEnd)
	{	//copy array
		auxL[rightEnd] = A[rightEnd];
	}
	return r;
}	

void Count_and_Print(string infile)
{
	string line;
	size_t comma = 0, comma2 = 0;
	int i = 0, j = 0;
	int cnt = 11;
	vector<User> UserArray;
	ifstream ifile; //input file 
	ofstream ofile; //output file
	ifile.open(infile, ios::in); //open file in read mode
	if(ifile.fail())
	{  
		cerr<<"Failed to open file"<<endl;
		exit(1);
	}
	else
	{
		while(!ifile.eof())
    	{
    		User user;
       		getline(ifile,line);
       		if(line == "\0")
       		{   //skip empty line
       			continue;
       		}
  			comma = line.find(',',0); //find comma
       		user.Name = line.substr(0,comma).c_str(); //set the user name
       		for(int j = 0; comma < line.size() && j != cnt-1;++j)
       		{
           		comma2 = line.find(',',comma + 1);
            	user.Songs[j].first = atoi(line.substr(comma + 1,comma2-comma-1).c_str()); //get the songs
            	user.Songs[j].second = j; //set index 
           		comma = comma2;
       		}
       		findRank(user.Songs, user.Rank); //get the rank
       		user.Inversion = Sort_Count(user.Rank, 10);
       		UserArray.push_back(user); //push user into vector
   		}
   		sort(UserArray.begin(), UserArray.end(), compInversion);
   		//print out to file
		ofile.open("file/SimilarityMetric.txt",ios::trunc); //open file if needed, create it first
		if(ofile.fail())
		{
			cerr<<"Failed to open file"<<endl;
			exit(1);
		}
		else
		{
			for(int k = 0; k<UserArray.size();++k)
			{
				ofile<<UserArray[k].Name;
				// for(int p = 0;p < 10;++p)
				// {
				// 	ofile<<','<<UserArray[k].Songs[p].first;
				// }
				ofile<<" Inversion is "<<UserArray[k].Inversion;
				ofile<<endl;
			}
   		}	
	}
	//close files
	ifile.close();
	ofile.close();
}

void findRank(pair<int, int> Songs[], int Rank[])
{
	sort(Songs, Songs+10, compSongsbyNum); //sort in descending	order
	int rank = 1;
	Rank[Songs[0].second] = rank; //set first one the first rank
	for(int i = 1; i < 10; ++i)
	{
		if(Songs[i].first == Songs[i-1].first)
		{
			Rank[Songs[i].second] = rank; //set same rank if value is the same with previous one
		}
		else
		{
			Rank[Songs[i].second] = ++rank; //else increase rank and assign the rank
		}
	}
	sort(Songs, Songs+10, compSongsbyIndex); //sort to recover original order
}