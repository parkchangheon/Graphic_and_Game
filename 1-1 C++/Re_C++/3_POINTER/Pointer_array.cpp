#include<iostream>
using namespace std;
class StatInfo
{
public:
	int hp;
	int defence;
	int attack;
};


int main()
{
	const int monsterCount = 10;
	StatInfo monsters[monsterCount];

	StatInfo* monster0 = monsters;
	monster0->hp = 100;
	monster0->defence = 20;
	monster0->attack = 10;

	StatInfo* monster1 = monsters + 1;
	monster1->hp = 200;
	monster1->defence = 40;
	monster1->attack = 20;
	
	StatInfo& monster2 = *(monsters + 2);
	monster2.hp = 300;
	monster2.defence = 80;
	monster2.attack = 40;

	for (int i = 0; i < 10; i++)
	{
		StatInfo& monster = *(monsters + i);
		monster.hp = 10 * i;
		monster.attack = 6 * i;
		monster.defence = 5 * i;
	}


}