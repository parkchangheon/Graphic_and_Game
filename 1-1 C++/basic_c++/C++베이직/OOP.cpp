#include<iostream>
using namespace std;

//객체지향 프로그래밍

//객체는 게임 내 모든 플레이어, 몬스터, 아이템 등 
//gameroom 같은 오브젝트도 객체

//Knight를 설계해보자
//속성(데이터) : hp, attackrage, position(x,y)
//기능(동작) : Move, Attack, Die

//struct <-> class 거의 같은데, public, private 차이
class Knight {
	
public:
	Knight() {  //디폴트 생성ㅅ자
		cout << "constuctor spawned" << endl;
		_hp = 100;
		_attack = 10;
		_posX = 0;
		_posY = 0;
	}
	 //복사 생성자 = 생성자인데 참조 타입으로 자기 자신을 받는다.
	Knight(const Knight& knight)  // 보통 만들어진 나이트 k1가 있을때, 또 만드는 것.   ==> 사용시 Knight k2(k1) 이런식으로 사용
	{   // 거의 99% 확률로 const를 붙여줘야함  ==> 다른애를 받아서 조작하는 경우는 거의 없기에 const를 붙여줌
		_hp = knight._hp;
		_attack = knight._attack;
		_posX = knight._posX;
		_posY = knight._posY;
	}

	//기타 생성자
	Knight(int hp) {
		_hp = hp;
		_attack = 10;
		_posX = 0;
		_posY = 0;
	}

	~Knight() {
		cout << "~Knight() 소멸자 호출" << endl;
	}
	//멤버함수(클래스 안에 있는)
	void Move(int x, int y);
	void Attack();
	void Die();

public:
	//멤버변수(클래스 안에 있는)
	int _hp;
	int _attack;
	int _posX;
	int _posY;
};

void Move(Knight* knight, int x, int y) { //일반함수
	knight->_posX = x;
	knight->_posY = y;
}


void Knight::Move(int x, int y)
{
	_posX = x;
	_posY = y;
	cout << "Move" << endl;
}

void Knight::Attack()
{
	cout << "Attack" << endl;

}

void Knight::Die()
{
	_hp = 0;
	cout << "Die" << endl;
}


//instantiate = 객체를 만든다.
int main()
{
	Knight k1;
	k1._hp = 100;
	k1._attack = 10;
	k1._posX = 0;
	k1._posY = 0;

	Knight k2;
	k2._hp = 80;
	k2._attack = 5;
	k2._posX = 1;
	k2._posY = 1;

	Move(&k1, 3, 3);
	k1.Move(2, 2);
	k1.Attack();
	k1.Die();
	return 0;
}



//Move(&k1, 3, 3);      
//00522777  push        3
//00522779  push        3
//0052277B  lea         eax, [k1]   //메모리로 올려준다 
//0052277E  push        eax         //eax 스택영역에 push
//0052277F  call        Move(0521442h)
//00522784  add         esp, 0Ch
//k1.Move(2, 2);
//00522787  push        2
//00522789  push        2
//0052278B  lea         ecx, [k1]   //그냥 레지스터에 들고있음
//0052278E  call        Knight::Move(052122Bh)




