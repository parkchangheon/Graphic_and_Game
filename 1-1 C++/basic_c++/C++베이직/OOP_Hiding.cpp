#include<iostream>
using namespace std;

//은닉성 - 캡슐화
//몰라도 되는 것은 깔끔하게 숨기겠다.

// 1) 정말로 위험하고 건드리면 안되는 경우
// 2) 다른 경로로 접근하길 원하는 경우
// public : 전부 다 사용 가능
// protected : 내 자손들한테만 허락
// private : 나만 쓸거야.


//상속 접근 지정자 : 다음 세대한테 부모님의 유산을 어떻게 물려줄지?
// 부모님한테 물려받은 유산을 꼭 나의 자손들한테도 똑같이 물려줘야 하지는 않는다.
//public: 부모님 유산 설계 그대로 (public-> public, protected-> protected, privated-> private) 로
//protected:(public-> protected, protected-> protected)
//private: 나까지만 잘 쓰고 자손들한테는 안물려줌 (public-> private, protected-> private)


class Car
{
public: //멤버접근 지정자
	void MoveHandle(){}
	void PushPedal() {}
	void OpenDoor() {}

	void TurnKey()  //사용자가 이것만 하면 아래 몰라도 되는 부분이 작동하게 설계
	{
		RunEngine();
	}

private:
	//여기는 사용자가 몰라도 되는 부분
	void DisassembleCar() {}
	void RunEngine() {}
	void ConnectCircuit() {}

public:
};

class Berserker
{
public:
	int GetHp() { return _hp; }
	void SetHp(int hp) {
		_hp = hp;
		if (_hp <= 50)
			SetBerserkerMode();
	}

private:
	// 사양 : 체력 50 미만일 때 버서커 모드 발동
	void SetBerserkerMode()
	{
		cout << "매우 강해짐 " << endl;
	}

private:
	int _hp = 100;
};

class SuperBerserker : public Berserker {  //상속 접근 지정자

};

int main()
{
	Berserker b;
	b.SetHp(20);

}