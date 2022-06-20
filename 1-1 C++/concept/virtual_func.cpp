//가상함수
//
//상속받을 클래스에서 재정의 할것으로 기대하고, 부모 클래스에서 정의해놓은 함수이다.
//virtual 예약어를 걸어놓고 생성이 가능하다.
//생성된 가상한수는 파생 클래스에서 재정의 하면, 이전에 정의되었던 내용들을 모두 새롭게 정의한 내용으로 교체한다.
//
//컴파일러는 함수를 호출할 때, 매우 복잡한 과정을 거치게 되는데, 컴파일러는 함수를 호출하는 코드를 컴파일 타임에
//고정된 메모리 주소로 변환한다. ==> 정적 바인딩
//일반 함수는 모두 정적 바인딩을 한다.
//
//일반함수를 오버로딩하게 된다면, 정적바인딩으로 인한 문제가 생길 수 있다.
//
//가상함수가 아닌 보통의 경우, 부모클래스형 포인터로 멤버함수를 호출할때, 컴파일러는 정적 타입을 보고
//이 타입에 맞는 멤버함수를 호출한다.


//#include<iostream>
//using namespace std;
//
//class Parent {
//public:
//	void print() {
//		cout << "이곳은 parent 입니다." << endl;
//	}
//};
//
//class Child : public Parent{
//public:
//	void print() {
//		cout << "이곳은 child 입니다." << endl;
//	}
//};
//
//
//void main() {
//	Parent* p = new Parent;
//	Child* c = new Child;
//
//	p->print();
//	p = c;
//	p->print();
//}

// 이런 경우 parent만 2번 호출된다.


//===========================

//#include<iostream>
//using namespace std;
//
//class Parent {
//public:
//	virtual void print() {
//		cout << "이곳은 parent 입니다." << endl;
//	}
//};
//
//class Child : public Parent {
//public:
//	virtual void print() {
//		cout << "이곳은 child 입니다." << endl;
//	}
//};
//
//
//void main() {
//	Parent* p = new Parent;
//	Child* c = new Child;
//
//	p->print();
//	p = c;
//	p->print();
//}
//parent, child 순으로 출력이 된다.




#include<iostream>
using namespace std;

class Parent {
public:
	virtual void func1() {
		cout << "이곳은 parent func1 입니다." << endl;
	}

	virtual void func2() {
		cout << "이곳은 parent func2 입니다." << endl;
	}

	void func3() {
		cout << "이곳은 parent func3 입니다." << endl;
	}
};

class Child : public Parent {
public:
	virtual void func1() {
		cout << "이곳은 child func1 입니다." << endl;
	}
};


void main() {
	Parent* p = new Parent;
	Child* c = new Child;

	p->func1();
	c->func1();

	p->func2();
	c->func2();

	p->func3();
	c->func3();
}