#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include <vector>

using namespace std;

typedef vector<int>::iterator VecIt;
typedef __int64 id;
using id2 = int;

id playerId = 0; //이런식으로도 활용가능

typedef void (*MyFunc)();
using MyFunc2 = void(*)();

template<typename T>
using List = std::list<T>;


enum PlayerType
{
	PT_Knight,
	PT_Mage,
	PT_Archer
};

enum MonsterType
{
	/*PT_Knight,*/ // 그대로 활용하면, PlayerType의 나이트랑 헷갈리고 컴파일 에러 뱉
	MT_Knight      // 그래서 이런식으로 앞에 약자를 붙여준다.
};

enum class ObjectType //이렇게 쓰면 다른 열거형 클래스에서 같은 이름써도 문제 없음
{
	//이름공간 관리가 가능
	//암묵적인 변환 금지. --> double value = ObejctType::Player이런게 안됨 할거면 static_cast<자료형>
	Player,
	Monster,
	Projectile
};

class Player
{
public:
	virtual void Attack()
	{
		cout << "Player!!" << endl;
	}
};


class Knight : public Player
{
public:
	void Attack() override  //재정의 override (내가 최초가 아니라 상속받은 함수 재정의 하는거다~) 
	{
		//final을 쓰면, 더이상 override하지 않는다는 뜻
		cout << "Knight!!" << endl;
	}
};




Knight* FindKnight()
{
	cout << "FindKnight" << endl;
	return nullptr;
}


void Test(int a)
{
	cout << "TEST(int)" << endl;
}

void Test(void* ptr)
{
	cout << "Test(*)" << endl;
}

class NullPtr
{
public:
	template<typename T>
	operator T* () const {  //포인터가 어떤 형식이라도 치환가능
		return 0;
	}

	//그 어떤 타입의 멤버 포인터와도 치환가능
	template<typename C, typename T>
	operator T C::* ()const
	{
		return 0;
	}

private :
	//void operator&() const; //주소값 추출을 막는다.(옛날 스타일)
	void operator&() const = delete; // 이게 보다 현대스타일

}_NullPtr;


int main()
{
	int* ptr = _NullPtr;   //nullptr 대신 임의로 만든, _NullPtr을 적용!
	Test(0);      //첫번째 버전 출력
	Test(NULL);   //첫번째 버전 출력
	Test(_NullPtr);// 두번째 버전 출력

	//override final



	auto knight = FindKnight();
	if (knight == _NullPtr)  //이 knight가 == 0이면 auto시 문제 발생 가능 농후.
	{
		
	}

	void(Knight:: * memFunc)();
	memFunc = &Knight::Test;

	if (memFunc == _NullPtr)
	{

	}

	

	return 0;
}