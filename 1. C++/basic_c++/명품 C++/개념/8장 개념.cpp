//protected 객체 접근

/*
#include<iostream>
#include<string>
using namespace std;

class Point {
protected:
	int x, y;
public:
	void set(int x, int y) { this->x = x; this->y = y; }
	void showPoint() { cout << "(" << x << "," << y << ")" << endl; }
};


class ColorPoint :public Point {
	string color;
public:
	void setColor(string color) { this->color = color; }
	void showColorPoint();
	bool equals(ColorPoint p);
};


void ColorPoint::showColorPoint() {
	cout << color << ":";
	showPoint();
}


bool ColorPoint::equals(ColorPoint p) {
	if (x == p.x && y == p.y && color == p.color)
		return true;
	else
		return false;
}



int main() {
	Point p;
	p.set(2, 3);
	//p.x = 5;
	//p.y = 5; 접근 불가

	p.showPoint();

	ColorPoint cp;
	//cp.x = 10;
	//cp.y = 10; 접근불가

	cp.set(3, 4);
	cp.setColor("RED");


	ColorPoint cp2;
	cp2.set(3, 4);
	cp2.setColor("RED");
	cout << ((cp.equals(cp2)) ? "true" : "false");
}

*/





// 클래스 생성자는 묵시적으로 상속에서 생성시엔, 기본생성자가 생성이 되는데, 이때 기본 생성자가 있어야함.
//ex)

//class A {
//public:
//	A() { cout << "생성자 A" << endl; }
//	A(int x) { cout << " 매개 변수 생성자 A " << x << endl; }
//};
//
//
//class B :public A {
//public:
//	B() {
//		cout << "생성자 B 호출";
//	}
//};




//ex2)

//class A {
//public:
//	A() { cout << "생성자 A" << endl; }
//	A(int x){ cout << "매개변수 생성자 A" << endl; }
//};
//
//
//class B : public  A {
//public:
//	B() { cout << "B 생성자"; }
//	B(int x):A(x+3){ cout << "매개변수 생성자 B" << endl; }
//};






//상속 관계와 생성자 매개 변수 전달

/*
#include<iostream>
#include<string>
using namespace std;


class TV {
	int size;
public:
	TV() { size = 20; }
	TV(int size) { this->size = size; }
	int getSize() { return size; }
};


class WideTV :public TV {
	bool videoIn;
public:
	WideTV(int size, bool videoIn) :TV(size) { this->videoIn = videoIn; }
	bool getVideo() { return videoIn; }
};


class SmartTV : public WideTV {
	string ipAddr;
public:
	SmartTV(string ipAddr, int size) :WideTV(size, true) { this->ipAddr = ipAddr; }
	string getIpAddr() { return ipAddr; }
};


int main(){
	SmartTV htv("192.0.0.1", 32);
	cout << "size=" << htv.getSize() << endl;
	cout << "videoIn=" << htv.getVideo() << endl;
	cout << "ip= " << htv.getIpAddr() << endl;
}
*/




//private 상속 사례
/*

#include<iostream>
using namespace std;

class Base {
	int a;
protected:
	void setA(int a) { this->a = a; }
public:
	void showA() { cout << a; }
};


class Derived :private Base {
	int b;
protected:
	void setB(int b) { this->b = b; }
public: 
	void showB() { cout << b; }
};


int main() {
	Derived x;
	x.a = 5; //a는 Derived 클래스에 상속되지만, private 멤버이므로 접근 불가
	x.setA(10); // private 멤버로 변경되어 Derived에 상속되었으므로, 클래스 외부에서 접근 불가
	x.showA();

	x.b = 10; //b가 private 변수이기 때문
	x.setB(); // protected 이기에 외부에서는 접근 금지
	x.showB(); // public 이기 떄문에 외부에서 접근 가능
}
*/






//protected 상속 사례
/*
#include<iostream>
using namespace std;

class Base {
	int a;
protected:
	void setA(int a) { this->a = a; }
public:
	void showA() { cout << a; }
};


class Derived :protected Base {
	int b;
protected:
	void setB(int b) { this->b = b; }
public:
	void showB() { cout << b; }
};


int main() {
	Derived x;
	x.a = 5; //a는 Derived 클래스에 상속되지만, private 멤버이므로 접근 불가
	x.setA(10); // protected 멤버로 변경되어 Derived에 상속되었으므로, 클래스 외부에서 접근 불가
	x.showA();

	x.b = 10; //b가 private 변수이기 때문
	x.setB(); // protected 이기에 외부에서는 접근 금지
	x.showB(); // public 이기 떄문에 외부에서 접근 가능
}
*/






// 상속이 중첩 될때 접근 지정 사례
/*
#include<iostream>
using namespace std;

class Base {
	int a;
protected:
	void setA(int a) { this->a = a; }
public:
	void showA() { cout << a; }
};


class Derived :private Base {
	int b;
protected:
	void setB(int b) { this->b = b; }
public:
	void showB() { 
		setA(5);   //setA는 Base의 protected 멤버이므로, 접근 가능
		showA();
		cout << b;
	}
};


class GrandDerived :private Derived {
	int c;
protected:
	void setAB(int x) {
		setA(x); // private 속성으로 변경되어, Derived 클래스에 상속되기 때문에, 접근 불가능
		showA(); // 마찬가지 
		setB(x); // protected 멤버이기 때문에 접근 가능
	}
};
*/





//다중 상속 선언 

//class MusicPhone :public MP3, public MobilePhone {
//public:
//	void dial();
//};




/*
#include<iostream>
using namespace std;

class Adder {

protected:
	int add(int a, int b) { return a + b; }
};


class Sub {
protected:
	int minus(int a, int b) { return a - b; }
};


class Calculator :public Adder, public Sub {
public:
	int calc(char op, int a, int b);
};


int Calculator::calc(char op, int a, int b) {
	int res = 0;
	switch (op) {
	case '+':
		res = add(a, b);
		break;
	case '-':
		res = minus(a, b);
		break;
	}
	return res;
}


int main() {
	Calculator handCalculator;
	cout << "2+4 = " << handCalculator.calc('+', 2, 4) << endl;

}
*/




//다중 상속의 문제점

// 만약 같은  즉 
/*
class BaseIO {
public:
	int mode;
};


class In :public BaseIO {
public:
	int readPos;
};

class Out :public BaseIO {
public:
	int writePos;
};


class InOut :public In, public Out {
public:
	bool safe;
};


int main() {
	InOut ioObj;
	ioObj.readPos = 10;
	ioObj.writePos = 10;
	ioObj.safe = true;
	ioObj.mode = 5; // 이떄 mode는 in의 것인지, out의 것인지 모호하다.

}
*/


//이러한 문제를 해결하기 위해 가상 상속을 사용
//class In : virtual public BaseIO {
//public:
//	int readPos;
//};
//
//class Out :virtual public BaseIO {
//public:
//	int writePos;
//};
