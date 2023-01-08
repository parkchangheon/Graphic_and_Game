#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

//rvalue 와 std::move의 활용

class Pet
{

};


class Knight {
public:

	Knight()
	{
		cout << "Knight()" << endl;
	}

	//복사 생성자
	Knight(const Knight& knight) 
	{
		cout << "Knight_const" << endl;
	}

	//이동생성자
	Knight(Knight&& knight)
	{

	}

	~Knight()
	{
		if (_pet)
			delete _pet;
	}

	//복사 대입 연산자.
	void operator=(const Knight& knight)
	{
		cout << "operator=(const Knight&)" << endl;

		//깊은복사
		_hp = knight._hp;
		if(!knight._pet)
			_pet = new Pet(*knight._pet);  //근데 얘까지 새로 복사할 예정은 아니었다...!
		//여기까지는 knight 내 데이터를 꺼내 쓰고 잘썻다~ 하면서 돌려주고, 내 버전을 새로 만들었다.
		//하지만 c++ 11 에서는 그냥 필요없는 애를 이동대상 즉 원본은 필요가 없다는 힌트를 준다.

	}

	//이동 대입 연산자.
	void operator=(Knight&& knight) noexcept    //자 knight는 더 이상 사용 안한다~
	{
		cout << "operator=(Knight&& knight)" << endl;

		//얕은 복사로 해도 ㄱㅊ
		_hp = knight._hp;
		_pet = knight._pet; //상대방꺼 내가 쓸거야.

		knight._pet = nullptr;


	}


	void PrintInfo()
	{


	}

public:
	int _hp = 100;
	Pet* _pet = nullptr;
};

void TestKnight_Copy(Knight knight) { }                  
void TestKnight_LValue_Copy(Knight& knight) { }          //knight원본을 줄게 알아서해!
void TestKnight_ConstLValue_Copy(const Knight& knight) {  /* 하지만 여기에 PrintInfo 같은 일반 함수들은 호출 못함..... ==> const가 붙은애들만 사용이 가능한 불편함이 있다. */  } //원본은 주지만 ReadOnly

void TestKnight_RValue_Copy(const Knight&& knight) {} //오른값 참조   // 원본을 주고 읽고쓰기도 하지만, 호출되고 knight는 활용 안할테니 너가 알아서해 (이동 대상) ;;;  원본 유지 안해도 됨

int main()
{
	// - lvalue : 단일식을 넘어서 계속 지속되는 개체
	// - rvalue : lvalue가 아닌 나머지 ( 임시값, 열거형, 람다, i++)

	Knight A1;

	TestKnight_Copy(A1); //복사
	TestKnight_LValue_Copy(A1); //복사x
	TestKnight_ConstLValue_Copy(Knight());  // RValue로 구현해서 임시적

	//TestKnight_RValue_Copy(A1); //반대로 이번엔 얘가 왼값을 못받음.
	TestKnight_RValue_Copy(Knight()); //우리가 볼떄는 임시값이 맞으나, 메모리 까보면, stack에 올라가있는데, 우리는 그걸 꺼내 쓰는거다
	TestKnight_RValue_Copy(static_cast<Knight&&>(A1)); //이렇게 왼값을 static_cast해도 들어가긴한다!


	Knight k2;
	k2._pet = new Pet();
	k2._hp = 1000;

	Knight k3;
	k3 = static_cast<Knight&&>(k2);   //k2가 가진 정보를 쓰되, 이제 k2는 안쓸거다.(혹시나 쓸 수 있으니 k2는 함수 내에서 nullptr로 셋업했다)
	//저기 저 k2의 pet을 뺏어온다. (k2의 정보를 k3에 대입하는 느낌)  
	//자 그럼 왜 쓰냐!!    => 복사는 데이터를 복사해오기 때문에 느리지만, 이동은 좀 더 빠르기 떄문이다.

	k3 = std::move(k2); //바로 윗줄의 static_cast해서 이동시키는 것과 같은 원리이다.
	//주로 unique 포인터에서 쓸텐데 이게 이동을 계~~속해서 (딱하나만 존재해야하는 포인터가 필요할 때 사용된다)   ==> 뒤에서 다뤄보겠다~!

	return 0;
}