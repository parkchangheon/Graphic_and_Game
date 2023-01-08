#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

//unscopped enum (범위없는 enum) 다른 공간에서 아래 열거형을 사용할 수 없게된다.
enum PlayerType
{
	Knight,
	Archer,
	Mage,
};

enum MonsterType
{
	MS_Knight, //이름이 겹친다.(MS로 변경)
};

//위의 문제를 해결하기 위해 아래와 같이 enum class로 만들어준다.
//이름공간 관리가 편하나, 암묵적 변환이 되질 않아 일일히 casting해줘야함...
enum class ObjectType
{
	Player,
	Monster,
	Projectile,
};

int main()
{
	double value = Knight; //일반적인 enum 활용법 (암묵적 변환)
	//double value2 = ObjectType::Player; //암묵적인 변환 x 
	double value2 = static_cast<double>(ObjectType::Player); //암묵적인 변환 x 

	int choice;
	cin >> choice;

	if (choice == Knight)
	{

	}

	if (choice == static_cast<int>(ObjectType::Player)) //enum클래스 (ObjectType::Player) 로 작성시 에러를 뱉음. 
	{

	}


	return 0;
}