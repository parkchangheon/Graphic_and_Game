#include<iostream>
using namespace std;

class Player
{
public:
	int _id;
};

int GenerateId()
{
	static int s_id = 1; //static 붙었으므로 스택에 올라가지 않고 데이터 영역에 올라간다.
	return s_id++;
}

class Marine {
public:
	int _hp; //각 객체에 종속적이게 된다


	void TakeDamage(int damage) {  //특정 멤버변수를 건드려서, 멤버변수의 느낌으로 쓸 수 있다.
		_hp -= damage;
	}
	static void SetAttack() { //전역함수마냥 독립적으로 움직임
		s_attack = 100;
	}
	static int s_attack; // 마린이라는 클래스 자체와 연관이 있음. 설계도 상으로만 존재
	//static 활용시 메모리할당이 한번만 하게 되어 메모리 사용 이점이 있다.
	//초기화를 화면 데이터 영역에 들어가고 
	//포기화 하지 않는 다면 .bss영역에 들어간다.
};

int Marine::s_attack = 0;

int main()
{
	Marine m1;
	m1._hp = 35;
	Marine::s_attack = 6;  //하나만 설정하면 모든 마린들의 공격력이 마뀐다.

	m1.TakeDamage(10);

	Marine m2;
	m2._hp = 14;

	Marine::SetAttack();
	Marine m3;
	m2._hp = 11;

}