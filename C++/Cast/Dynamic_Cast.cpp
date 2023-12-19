/* 
* dynamic casting은 같은 상속계층 내부에서 캐스트에 대한 실행시간 검사를 제공한다
* Ptr / Ref 를 캐스트할때 이용가능
* dynamic_cast는 실행시간검사를 제공한다.
* Ptr에 대해서 캐스팅이 적합하지 않으면 => nullptr을
* Ref에 대해서는 std::bad_cast 익센셥이 발생한다.

*/



#include<iostream>
using namespace std;

class Base
{
public:
	virtual ~Base() = default;
};

class Derived : public Base
{
public:
	virtual ~Derived() = default;
};

int main()
{
	Base* b;
	Derived* d = new (Derived);

	b = d;

	d = dynamic_cast<Derived*>(b);
}