// 상속

/*
#include<iostream>
using namespace std;

class phone {
	void call();
	void receive();
};


class MobilePhone : public phone {
	void connectWireless();
	void recharge();
};

class MusicPhone : public MobilePhone {
	void downloadMusic();
	void play();
};

*/




#include<iostream>
#include<string>
using namespace std;

class point {
	int x, y;
public :
	void set(int x, int y) { this->x = x, this->y = y; }
	void showPoint() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};


class colorpoint : public point {
	string color;

public :
	void setColor(string color) { this->color = color; }
	void showColorPoint();
};

void colorpoint::showColorPoint(){
	cout << color << ":";
	showPoint();
}
/*
int main() {
	point p;
	colorpoint cp;
	cp.set(3, 4);
	cp.setColor("Red");
	cp.showColorPoint();
}
*/


/*
int main() {
	colorpoint cp;
	colorpoint* pder = &cp;
	point* pbase = pder; // 업캐스팅 ( 파생 클래스 포인터가 기본 클래스 포인터에 치환)

	pder->set(3, 4);
	pbase->showPoint();

	pder->setColor("Green");
	pder->showColorPoint();
//결론적으로 pbase는 point 형식을 따르므로, pder의 상속받은 point 부분만 접근 가능
}

*/



//protected 접근 지정 
//접근 지정자

// private, public, protected




/*
#include<iostream>
using namespace std;

class base {
public:
	virtual void f() {
		cout << "base::f() called" << endl;
	}
};

class derived : public base {
public:
	virtual void f() { cout << "derived::f() called " << endl; }
};

int main() {
	derived d, *pder;
	pder = &d;
	pder->f(); //=> 여기선 가리킨대로 잘 반환

	base* pbase;
	pbase = pder;
	pbase->f();  //여기는 기존 함수가 상실되어 동적바인딩으로 새로운 함수 실행
}
// 동적 바인딩이란 파생클래스에 대해, 기본 클래스에 대한 포인터로,
// 가상함수를 호출하는 경우
//객체 내에 오버라이딩한 파생 클래스의 함수를 찾아 실행
*/



