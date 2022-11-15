#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include <vector>

using namespace std;
//오른값 참조 (rvalue - reference)
//int a = 3;에서 3이 오른값 

class Pet
{
public :

};

class Knight
{
public:
	Knight()
	{
		cout << "Knight()" << endl;
	}

	//복사 생성자.
	Knight(const Knight& knight) // 생성되자마자 뭔갈 만듦
	{
		cout << "Knight()" << endl;
		
		//깊은 복사
		_hp = knight._hp;
		if (knight._pet)
			_pet = new Pet(*knight._pet);

	}



	~Knight()
	{
		if (_pet)
			delete _pet;
	}

	void operator=(const Knight* knight)
	{
		cout << "operator=(const knights&)" << endl;
	}


	void operator=(Knight&& knight) noexcept
	{

		cout << "operator=(Knight&&)" << endl;

		_hp = knight._hp;
		_pet = knight._pet;

		knight._pet = nullptr;
	}



public:
	int _hp = 100;
	Pet* _pet;
};


void TestKnight_Copy2(Knight* k) {}


void TestKnight_Copy(Knight k) {}
void TestKnight_LValueRef(Knight& knight) {}   //왼 값 원본으로 하고 싶은거 다해
void TestKnight_ConstLValueRef(const Knight& knight) {} //왼 값 원본은 넘기되 암것도 못해 


void TestKnight_RValue(Knight&& knight) { };   //오른값 참조 ==> 읽고 쓰기도 다되는데, 더이상 활용하지 않아! 이동대상


int main()
{
	//왼값(lvalue) vs 오른값(rvalue)
	// - lvalue : 단일식을 넘어서 계속 지속되는 개체
	// - rvalue : lvalue가 아닌 나머지 (임시값, 열거형,람다, i++ 등) 

	Knight k1;

	TestKnight_Copy2(&k1);


	TestKnight_Copy(k1);
	TestKnight_LValueRef(k1);
	TestKnight_ConstLValueRef(Knight());


	TestKnight_RValue(Knight()); //일반적인 왼값 k1을 못받는다. -> 원래는 못받던 Knight() 오른값을 받음.
	TestKnight_RValue(static_cast<Knight&&>(k1));





	Knight k2;
	k2._pet = new Pet();
	k2._hp = 1000;

	//이동 (뺏어온다)
	Knight k3;
	//k3 = static_cast<Knight&&>(k2);
	//보통은 아래와 같이 많이 쓴다.
	k3 = std::move(k2);

	//이것을 (오른값참조) -> 이동을 쓰는 경우는 
	//스마트 포인터를 쓸때 많이 쓰는데, 
	//여기서 유니크 포인터는 포인터가 딱 하나만 존재하도록 할때 씀
	std::unique_ptr<Knight> uptr = std::make_unique<Knight>();
	std::unique_ptr<Knight> uptr2 = std::move(uptr); //포인터를 이동 시킬때 사용

	
	//즉 원본을 유지 하지 않아도 되는 데이터, 혹은 데이터 전체를 이양할때 필요하다.
	


	return 0;
}