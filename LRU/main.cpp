#include "LRU.hpp"

int main(void)
{
	cout<<"Please enter an integer for capacity N and ratio R:"<<endl;
	int capacity;
	double ratio;
	cin>>capacity>>ratio;

	LRU LRUCache = LRU(capacity);
	list<Node> Cache;
	list<Node>::iterator iter2;
	cout<<"For LRU:"<<endl;
	LRUCache.set(1, 1);
	LRUCache.set(3, 3);
	LRUCache.set(2, 2);
	LRUCache.set(1, 1);
	LRUCache.set(5, 5);
	LRUCache.set(4, 4);
	LRUCache.set(3, 3);
	Cache = LRUCache.getCache();
	cout<<"Cache:"<<endl;
	for(iter2 = Cache.begin();iter2!=Cache.end();++iter2)
	{    //print out the data in cache
		cout<<iter2->Value<<" "; 
	}
	LRUCache.set(7, 7);
	LRUCache.set(6, 6);
	LRUCache.set(8, 8);
	Cache = LRUCache.getCache();
	cout<<endl<<"Cache:"<<endl;
	for(iter2 = Cache.begin();iter2!=Cache.end();++iter2)
	{
		cout<<iter2->Value<<" "; 
	}
	LRUCache.set(9, 9);
	Cache = LRUCache.getCache();
	cout<<endl<<"Cache:"<<endl;
	for(iter2 = Cache.begin();iter2!=Cache.end();++iter2)
	{
		cout<<iter2->Value<<" "; 
	}
	LRUCache.set(5, 5);
	Cache = LRUCache.getCache();
	cout<<endl<<"Cache:"<<endl;
	for(iter2 = Cache.begin();iter2!=Cache.end();++iter2)
	{
		cout<<iter2->Value<<" "; 
	}
	cout<<endl;

	cout<<"For modified LRU:"<<endl;
	LRU LRUCache2 = LRU(capacity, ratio);
	list<Node> Cache2;
	LRUCache2.set2(1, 1);
	LRUCache2.set2(3, 3);
	LRUCache2.set2(2, 2);
	LRUCache2.set2(1, 1);
	LRUCache2.set2(5, 5);
	LRUCache2.set2(4, 4);
	LRUCache2.set2(3, 3);
	Cache2 = LRUCache2.getCache();
	cout<<"Cache:"<<endl;
	for(iter2 = Cache2.begin();iter2!=Cache2.end();++iter2)
	{
		cout<<iter2->Value<<" "; 
	}
	LRUCache2.set2(7, 7);
	LRUCache2.set2(6, 6);
	LRUCache2.set2(8, 8);
	Cache2 = LRUCache2.getCache();
	cout<<endl<<"Cache:"<<endl;
	for(iter2 = Cache2.begin();iter2!=Cache2.end();++iter2)
	{
		cout<<iter2->Value<<" "; 
	}
	LRUCache2.set2(6, 6);
	Cache2 = LRUCache2.getCache();
	cout<<endl<<"Cache:"<<endl;
	for(iter2 = Cache2.begin();iter2!=Cache2.end();++iter2)
	{
		cout<<iter2->Value<<" "; 
	}
	LRUCache2.set2(5, 5);
	Cache2 = LRUCache2.getCache();
	cout<<endl<<"Cache:"<<endl;
	for(iter2 = Cache2.begin();iter2!=Cache2.end();++iter2)
	{
		cout<<iter2->Value<<" "; 
	}
	LRUCache2.set2(9, 9);
	Cache2 = LRUCache2.getCache();
	cout<<endl<<"Cache:"<<endl;
	for(iter2 = Cache2.begin();iter2!=Cache2.end();++iter2)
	{
		cout<<iter2->Value<<" "; 
	}
	cout<<endl;
	return 0;
}