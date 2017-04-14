#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

#define NotFound -1
#define ElemType1 int //key type
#define ElemType2 int  //value type
using namespace std;

struct Node
{
	ElemType1 Key;
	ElemType2 Value;
};

#ifndef LRU
class LRU
{
	private:
		int Capacity;  //the capacity
		double Ratio; //the ratio
		list<Node> Cache; //use double linkedlist
		int M; //the boundary between young and old
		list<Node>::iterator MIter; //the position of M
		unordered_map<ElemType1, list<Node>::iterator> CacheMap; //cache pool in hashmap, store the key and iterator

	public:
		LRU(int capacity)
		{
			this->Capacity = capacity; //when use lrucache, need to set capacity
		} //constructor 1
		

		LRU(int capacity, double ratio)
		{
			this->Capacity = capacity;
			this->Ratio = ratio;
			this->M = capacity - (int)(capacity*ratio);
		}//constructor 2 for modified LRU

		~LRU(){cout<<"Destroyed"<<endl;}; //destructor

		void set(ElemType1 key, ElemType2 value)
		{
			//exam its existence
			unordered_map<ElemType1, list<Node>::iterator>::iterator FindKey;
			FindKey = CacheMap.find(key); //find the key
			if(FindKey!=CacheMap.end())
			{   //if found
			 	list<Node>::iterator FindValue;
			 	FindValue = FindKey->second; //find the value
			 	FindValue->Value = value;
			 	if(FindValue != Cache.begin())
			 	{  //if item is not on front, bring to the front
			 		Cache.splice(Cache.begin(), Cache, FindValue, next(FindValue));
			 	}
			}
			else
			{   //exam the capacity
				if(Cache.size() == this->Capacity)
				{  //if full
					ElemType1 FindLast = Cache.back().Key; //find the last node
					Cache.pop_back(); //delete from list
					CacheMap.erase(FindLast); //delete from map
				}
				Node newNode = {key, value}; 
				Cache.push_front(newNode); //add new node to front
				CacheMap.insert(make_pair(key, Cache.begin())); //store the key and iterator
			}
		}

		ElemType2 get(ElemType1 key)
		{
			unordered_map<ElemType1, list<Node>::iterator>::iterator FindKey;
			FindKey = CacheMap.find(key); //find the key
			if(FindKey!=CacheMap.end())
			{   //if find the key
				list<Node>::iterator FindValue;
			 	FindValue = FindKey->second; //find the value
			 	if(FindValue != Cache.begin())
			 	{   //bring the node visited to front
			 		Cache.splice(Cache.begin(), Cache, FindValue, next(FindValue));
			 	}
			 	return FindValue->Value; //return value we want to visit
			}
			return NotFound;
		}

		//get cache
		list<Node> getCache()
		{
			return this->Cache;
		}

		void set2(ElemType1 key, ElemType2 value)
		{
			unordered_map<ElemType1, list<Node>::iterator>::iterator FindKey;
			FindKey = CacheMap.find(key); //find the key
			if(FindKey!=CacheMap.end())
			{   //if found
		 		list<Node>::iterator FindValue;
				FindValue = FindKey->second; //find the value
				FindValue->Value = value;
				if(FindValue != Cache.begin())
				{  //if item is not on front, bring to the front
			 		Cache.splice(Cache.begin(), Cache, FindValue, next(FindValue));
			 	}
			 	if(Cache.size() > this->M)
			 	{    //for cache size over boundary, reset M
			 		list<Node>::iterator tmpIter = Cache.end();
			 		int i = this->Capacity-this->M;
			 		while(i>0)
			 		{
			 			--tmpIter;
			 			--i;
			 		}
			 		this->MIter = tmpIter;
			 	}
			}
			else
			{
				if(Cache.size() < this->M)
				{   //smaller than bound
					Node newNode = {key, value}; 
					Cache.push_front(newNode); //add new node to front
					CacheMap.insert(make_pair(key, Cache.begin())); //store the key and iterator	
					if(Cache.size() == this->M)
            		{	//if full for young, set the M
            			this->MIter = Cache.end();
            		}    
				}
				else
				{
					if(Cache.size() == this->Capacity)
					{  //if full for total cache
						ElemType1 FindLast = Cache.back().Key; //find the last node
						Cache.pop_back(); //delete from list
						CacheMap.erase(FindLast); //delete from map
					}
					Node newNode = {key, value}; //new node
					Cache.insert(this->MIter, newNode); //add new node to end, after the bound
					list<Node>::iterator tmpIter = Cache.end();
					while((--tmpIter)->Value != newNode.Value);
					CacheMap.insert(make_pair(key, tmpIter)); //store the key and iterator
					--this->MIter; //reset the position of M
				}
			}	 
		}

		ElemType2 get2(ElemType1 key)
		{
			unordered_map<ElemType1, list<Node>::iterator>::iterator FindKey;
			FindKey = CacheMap.find(key); //find the key
			if(FindKey!=CacheMap.end())
			{   //if find the key
				list<Node>::iterator FindValue;
			 	FindValue = FindKey->second; //find the value
			 	if(FindValue != Cache.begin())
			 	{   //bring the node visited to front
			 		Cache.splice(Cache.begin(), Cache, FindValue, next(FindValue));
			 	}
			 	list<Node>::iterator tmpIter = Cache.end();
			 	int i = this->Capacity-this->M;
			 	while(i>0)
				{
		 			--tmpIter;
		 			--i;			 		
		 		}
			 	this->MIter = tmpIter;
			 	return FindValue->Value; //return value we want to visit
			}
			return NotFound; //if not found, return NotFound
		}
};
#endif