//오버라이딩, 가상함수
/*
#include<iostream>
using namespace std;

class Base {
public:
	virtual void f() { cout << "Base::f() called" << endl; }

};

class Derived :public Base {
public:
	virtual void f() { cout << "Derived::f() called" << endl; }
};

void main() {
	Derived d, * pDer;
	pDer = &d;
	pDer->f();

	Base* pBase;
	pBase = pDer;
	pBase->f();
}
*/
// 저 위에 두 f() 함수가 가상함수로 설정이 안되었다면 그냥 함수 재정의가 되었을 것이나, virtual 가상함수로 정의했으므로, 
//결과는 //Derived::f() called 가 두번 나온다

// 이 동적 바인딩을 통해 Derived f()가 호출.
// Base f()에 대한 모든 호출은 실행 시간 중에 Derived의 f() 함수로 동적 바인딩 된다.


//오버라이딩의 목적은, 각 파생클래스들이 자신의 목적에 맞게 가상함수를 재정의 하도록 하는것.
// 결국 오버라이딩으로 다형성의 실현 할 수 있다.









//오버라이딩의 사례
/*
#include<iostream>

using namespace std;

class Base {
public:
	virtual void f() {cout << "Base::f() called" << endl;}
};

class Derived :public Base {
public:
	void f() { cout << "Derived::f() called" << endl; }
};

class GrandDerived :public Derived {
public:
	void f() { cout << "GrandDerived::f() called" << endl; }
};



int main() {
	GrandDerived g;
	Base* bp;
	Derived* dp;
	GrandDerived* gp;
	bp = dp = gp = &g;

	bp->f();
	dp->f();
	gp->f();
}

*/




// 오버라이딩에 의해 무시된 기본 클래스의 가상함수를 호출할 방법이 있다.  ==>범위 지정 연산자 ::을 쓰는 것이다.
/*
#include<iostream>
using namespace std;

class Shape {
public:
	virtual void draw() { cout << "--Shape--"; }
};


class Circle : public Shape {
public:
	int x;
	virtual void draw() { 
		Shape::draw(); 
		cout << "Circle" << endl;
	}
};

int main() {
	Circle circle;
	Shape* pShape = &circle;

	pShape->draw();
	pShape->Shape::draw();
}
*/




// 범위 연산자의 다른 쓰임새 ( 전역변수 호출 가능)
/*
#include<iostream>
using namespace std;

void sendMessage(const char* msg)
{
	cout << msg << endl;
}

class Window {
public:
	void sendMessage(const char* msg) {
		cout << "window msg : " << msg << endl;
	}
	void run() {
		::sendMessage("Global Hello");
		sendMessage("Local Hello");
	}
};

int main() {
	Window window;
	window.run();
}
*/







// 소멸자에 virtual를 항상 붙여 주는것이 탈이 안난다.
/*
#include<iostream>
using namespace std;

class Base {
public:
	virtual ~Base() { cout << "~Base()" << endl; }
};

class Derived : public Base {
public:
	virtual ~Derived() { cout << "~Derived()" << endl; }
};


int main() {
	Derived* dp = new Derived();
	Base* bp = new Derived();

	delete dp;
	delete bp;
}

*/




// 오버로딩은 매개 변수의타입이나 개수가 다른 함수들을 여러개 중복 작성하는 것이다.




/*
#include<iostream>
#include "shape.h"
#include "Circle.h"
#include "Rect.h"
#include "Line.h"

using namespace std;


int main() {
	Shape* pStart = NULL;
	Shape* pLast;

	pStart = new Circle();
	pLast = pStart;


	pLast = pLast->add(new Rect());
	pLast = pLast->add(new Circle());
	pLast = pLast->add(new Line());
	pLast = pLast->add(new Rect());

	// 현재 연결된 모든 도형을 화면에 그린다
	Shape* p = pStart;
	while (p != NULL) {
		p->paint();
		p = p->getNext();
	}


	p = pStart;
	while (p != NULL) {
		Shape* q = p->getNext();
		delete p;
		p = q;
	}
}
*/






//추상클래스 구현 연습
/*
#include<iostream>

using namespace std;

class Calculator {
public:
	virtual int add(int a, int b) = 0;
	virtual int substract(int a, int b) = 0;
	virtual double average(int a[], int size) = 0;
};


class GoodCalc :public Calculator {
public:
	int add(int a, int b) { return a + b; }
	int substract(int a, int b) { return a - b; }
	double average(int a[], int size) {
		double sum = 0;
		for (int i = 0; i < size; i++)
			sum += a[i];
		return sum / size;
	}
};


int main() {
	int a[] = { 1,2,3,4,5 };
	Calculator* p = new GoodCalc();
	cout << p->add(2, 3) << endl;
	cout << p->substract(2, 3) << endl;
	cout << p->average(a, 5) << endl;
	delete p;
}
*/






#include<iostream>
using namespace std;


class Calculator {
	void input() {
		cout << "정수 2개를 입력하시오 : ";
		cin >> a >> b;
	}
protected:
	int a, b;
	virtual int calc(int a, int b) = 0;

public:
	void run() {
		input();
		cout << "계산된 값은" << calc(a, b) << endl; 
	}
};


class Adder : public Calculator {
public:
	int calc(int a, int b) {
		return a + b;
	}
};

class Substractor : public Calculator {
public:
	int calc(int a, int b) {
		return a - b;
	}
};

int main() {
	Adder adder;
	Substractor substractor;

	adder.run();
	substractor.run();
}