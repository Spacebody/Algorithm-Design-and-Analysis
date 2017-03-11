//definition of class

#include <string>
#include <map> //use map of STL

using namespace std; //use namespace
typedef map<string, int> Rank_Inverse; //key is name and value is rank
typedef map<int, string> Rank_Map; //key is rank and value is name 


class Human
{
	private:
		string Name; //name of the object
		string Partner; //partner name
		bool IsSingle; //state
		Rank_Map rank; //rank map
		Rank_Inverse rank_inverse; //in order to find name according to rank
		int counter;			 
		
	public:
		Human(){}; //constructor
		~Human(){};//destructor
		//get name
		string getName()
		{
			return this->Name;
		}

		//get partner name
		string getPartner()
		{
			return this->Partner;
		}

		//get state
		bool getState()
		{
			return this->IsSingle;
		}

		//set object name
		void setName(string Name)
		{
			this->Name = Name; 
		}

		//set partner name
		void setPartner(string PartnerName)
		{
			this->Partner = PartnerName;
		}

		//set object state
		void setState(bool state)
		{
			this->IsSingle = state;
		}

		//set counter value for rank record
		void setCounter()
		{
			this->counter = 0;
		}

		//list initialization
		void initList(int j, string name)
		{
			rank.insert(pair<int,string>(j+1, name));
			rank_inverse.insert(pair<string, int>(name, j+1));
		}

		//find rank according name
		int NametoRank(string Name)
		{
			return rank_inverse[Name];
		}

		//find next target
		string FindNext()
		{
			string name = rank[++(this->counter)];
			rank.erase(this->counter);
			return name;
		}

		//exam whether to break up
		bool breakUp(int CmpRank, int PartnerRank)
		{
			return CmpRank > PartnerRank;
		}

};

