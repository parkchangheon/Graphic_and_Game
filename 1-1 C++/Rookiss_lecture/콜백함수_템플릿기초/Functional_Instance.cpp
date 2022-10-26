#include<iostream>
using namespace std;

void HelloWorld()
{
	cout << "Hello World " << endl;
}
void HelloNumber(int number)
{
	cout << "Hello World " << number << endl;
}

class Knight {
public:
	void AddHp(int addHp)
	{
		_hp += addHp;
	}

private:
	int _hp = 100;
};

class Functor
{
public:
	void operator()()  //()를 오버로딩 할거고, ()는 함수니까 붙여주는 것이다.
	{
		cout << "Functor Test" << endl;
		cout << _value << endl;
	}

	bool operator()(int num)
	{
		cout << "Functor Test2" << endl;
		_value += num;
		cout << _value << endl;

		return true;
	}

private:
	int _value = 0;
};

class MoveTask
{
public:
	void operator()()
	{
		cout << "해당 좌표로 플레이어 이동" << endl;
	}

public:
	int _playerId;
	int _posX;
	int _posY;
};



int main()
{
	//함수 객체 (Functor) : 함수처럼 동작하는 객체 
	// 
	//함수 포인터 선언
	void(*pfunc)(void);
	pfunc = &HelloWorld; // 동작을 넘겨줄때 유용함
	(*pfunc)();
	
	//함수 포인터의 단점
	// 1) 시그니처가 안맞으면 사용할 수 없다.
	// 2) 상태를 가질 수 없다.
	//pfunc = &HelloNumber;

	//함수 객체란?
	//함수처럼 동작하는 객체 -> 일단 Class를 만들어준다.
	//() 연산자 오버로딩을 통해 함수처럼 사용한다.
	HelloWorld();

	Functor functor; //함수 포인터와 다르게 상태값을 들고 있다.
	functor();
	bool ret = functor(3);

	//어쩔때 써야할까??
	//MMO에서 함수 객체를 사용하는 예시 
	//클라 <-> 서버
	//서버 : 클라가 보내준 네트워크 패킷을 받아서 처리
	// 
	// 
	//ex) 클라 : 나(5,0) 좌표로 이동시켜줘! 라는 패킷을 보내면 => 서버가 체크하고 이동시킴
	//Command Pattern
	MoveTask task;
	task._playerId = 100;
	task._posX = 5;
	task._posY = 0;

	//실제로 실행하는 부분
	task();

	return 0;
}