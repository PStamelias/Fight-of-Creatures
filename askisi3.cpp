#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<sstream>
using namespace std;
string Names_For_GoodCreatures[]={"Dog","Cat","Mouse","Rat","Sheep","Chicken","Squarell","Elephant","Fish","Dolphin","Seal","Pigeon","Human","Horse",
"Hamster"};
string Names_For_BadCreatures[]={"Wolf","Snake","Lion","Tiger","Puma","Crocodile","Shark","Bull","Eagle","Aligator","Anaconda","Cobra","Dinosaur","Owl"
"Dragon"};
int option;
int number;
int position;
class creature_society;
int counter_of_zombies;
int counter_of_goodcreatures;
int counter_of_badcreatures;
class creature{
	protected:
		string name;
		int life;
		creature_society *p;
	public:
		creature(int L,creature_society *a)
		{
				this->life=L;
				this->p=a;
				cout<<"i created a creature"<<endl;
		}
		creature(const creature& pl)
		{
				this->name=pl.name;
				this->life=pl.life;
		}
		bool is_a_zombie()
		{
				if(this->life==0)
					return true;
				else 
					return false;
		}
		void set_name(int i,int j)
		{
			int position=i;
			if(j==0)//good_creatures
			{
				string result;
				stringstream sstm;
				result=Names_For_GoodCreatures[rand()%14];
				sstm << result << position;
				this->name = sstm.str();
			}
			if(j==1)//bad_creatures
			{
				string result;
				stringstream sstm;
				result=Names_For_BadCreatures[rand()%14];
				sstm << result << position;
				this->name = sstm.str();
			}
		}
		virtual void clone(creature**)=0;
		virtual bool is_a_good()=0;
		virtual
		void bless(int position)
		{
			if( this->is_a_zombie()==false)
			{
				this->life++;
				cout<<"the life of creature increased by one unit "<<endl;
			}
		}
		void beat()
		{
			if(this->is_a_zombie()==false)
			{
				this->life--;
				cout<<"the life of creature reduced by one unit "<<endl;
			}
		}
		virtual
		~creature()
		{
				cout<<"i destroyed a creature"<<endl;
		}
};

class good_creature:public creature{
	private:
		int good_thrsh;
	public:
		good_creature(int L,int good_thrsh,int i,creature_society *p):creature(L,p)
		{
			cout<<"i created a good creature"<<endl;
			this->good_thrsh=good_thrsh;
			creature::set_name(i,0);
		}
		void clone(creature*   * object)//creature* *object=&CreatureTable[position+1]
		{
			delete *object;
			*object=new good_creature(*this);
		}
		void bless(int position);
		bool is_a_good()
		{
			if(this->is_a_zombie()==false)
				return true;
		}
		~good_creature()
		{
			cout<<"i destroyed a good creature"<<endl;
		}
};
class bad_creature:public creature{
	private:
		int bad_thrsh;
	public:
		bad_creature(int L,int bad_thrsh,int i,creature_society *p):creature(L,p)
		{
			cout<<"i created a bad creature"<<endl;
			this->bad_thrsh=bad_thrsh;
			creature::set_name(i,1);
		}
		void bless(int position);
		bool is_a_good()
		{
			if(this->is_a_zombie()==false)
				return false;
		}
		void clone(creature** onoma)
		{
			delete *onoma;
			*onoma=new bad_creature(*this);
		}
		~bad_creature()
		{
			cout<<"i destroyed a bad creature"<<endl;
		}
};
class creature_society{
	private:
		creature*   *CreatureTable;
	public:
		creature_society(int N,int L,int good_thrsh,int bad_thrsh)
		{
			CreatureTable=new creature*[N];	
			number=N;	
			cout<<"i created a society of creatures"<<endl;
			for(int i=0;i<N;i++)
			{
				int epilogi;
				epilogi=rand()%2;
				if(epilogi==0)//bad creature
					CreatureTable[i]=new bad_creature(L,bad_thrsh,i,this);
				if(epilogi==1)//good creature
					CreatureTable[i]=new good_creature(L,good_thrsh,i,this);
			}
		}
		void bless(int i)
		{
			CreatureTable[i]->bless(i);
		}
		void beat(int i)
		{
			CreatureTable[i]->beat();
		}
		void clone_next(int position)
		{
			if(position!=number-1)
				CreatureTable[position]->clone(&CreatureTable[position+1]);
			else
				CreatureTable[position]->clone(&CreatureTable[0]);
		}
		void clone_zombies(int position)
		{
			for(int i=position+1;i<number;i++)
			if(CreatureTable[i]->is_a_zombie()==true)	
				CreatureTable[position]->clone(&CreatureTable[i]);
			
		}
		int no_of_good()
		{
			for(int i=0;i<number;i++)
			{
				if(CreatureTable[i]->is_a_good()==true)
					counter_of_goodcreatures++;
			}
			return counter_of_goodcreatures;
		}
		int no_of_zombies()
		{
			for(int i=0;i<number;i++)
			{
				if(CreatureTable[i]->is_a_zombie()==true)
					counter_of_zombies++;
			}
			return counter_of_zombies ;
		}
		~creature_society()
		{
			for(int i=0;i<number;i++)
			{
				delete CreatureTable[i];
			}
			cout<<"i destroyed a society of creatures"<<endl;
		}
};
void good_creature::bless(int position){

	creature::bless(position);
	if(this->life>good_thrsh)
		p->clone_next(position);
}

void bad_creature::bless(int position)
{
	creature::bless(position);
	if(this->life>bad_thrsh&&position!=number-1)
		p->clone_zombies(position);
}

int main(int argc,char* argv[])
{
	srand(time(NULL));
	int N,M,L,good_thrsh,bad_thrsh;
	//input 
	N=atoi(argv[1]);
	M=atoi(argv[2]);
	L=atoi(argv[3]);
	good_thrsh=atoi(argv[4]);
	bad_thrsh=atoi(argv[5]);
	//1o erwtima
	creature_society A(N,L,good_thrsh,bad_thrsh);
	//2o erwtima 
	for(int i=0;i<M;i++)
	{
			position=rand()%N;
			option=rand()%2;
			if(option==0)//beat 
				A.beat(position);
			else//bless
				A.bless(position);
	}
	//3o erwtima
	if(A.no_of_good()==N)
		cout<<"Good Dominates the world"<<endl;
	else if(A.no_of_zombies()==N)
		cout<<"This is a dead society"<<endl;
	else
		cout<<"Try again to improve the world"<<endl;
	return 0;
}

