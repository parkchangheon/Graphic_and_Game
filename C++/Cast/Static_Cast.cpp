#include<iostream>

using namespace std;

class Base
{
public:
	virtual ~Base() = default;

public:
	string name;
};

class Derived : public Base
{
public:
	virtual ~Derived() = default;

public:
	string d_name;
};


int main()
{
	Base* base = nullptr;
	Derived* derived = new Derived();

	base = derived;
	base->name = "baseClassName";
	//base->d_name = "DerivedClassName";	Base는 derived 멤버에 접근할 수 없다.
	
	derived = static_cast<Derived*>(base);

	derived->d_name = "DerivedClassName";
	cout << derived->name << " and " << derived->d_name;

	
	//ps
	Base* base2 = new Base();
	Derived* derived2 = static_cast<Derived*>(base2);

	
	//에러1
	//컴파일 타임에는 문제가 없겠지만, 런타임에서는 크래시가 날 수 있다.	(객체 범위를 벗어난 영역의 메모리를 덮어쓰기) ==> Dynamic_cast를 사용해야한다.
	//cout << derived2->d_name;	//Crash!
	//cout<< derived2->d_name;	//Crash!

	//에러2
	//double* dou = new double(3.15);
	// int* integer = dou;
	// int* integer3 = static_cast<int*>(dou); 이 2개는 애초에 말이 안됨.

	// int* integer2 = (int*)(dou); //명시적 형변환으로 바꾸긴 했으나, 말도 안되는 결과값이 나옴.
}