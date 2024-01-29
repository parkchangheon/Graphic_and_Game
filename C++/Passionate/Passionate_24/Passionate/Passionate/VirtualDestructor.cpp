#include "VirtualDestructor.h"

VDFirst::VDFirst(const char* str)
{
	strOne = new char[strlen(str) + 1];
}

VDFirst::~VDFirst()
{
	cout << "~First()" << endl;
	delete []strOne;
}

VDSecond::VDSecond(const char* str1, const char* str2) : VDFirst(str1)
{
	strTwo = new char[strlen(str2) + 1];
}

VDSecond::~VDSecond()
{
	cout << "~Second()" << endl;
	delete []strTwo;
}


//int main()
//{
//	VDFirst* ptr = new VDSecond("simple", "complex");
//	delete ptr;
//	return 0;
//}

// ~First 만 호출이 된다.
// 객체 소멸을 VDFirst형 포인터로 명령하여, ~First만 호출이 된것.


// VDSecond는 메모리 누수가 발생한다.
// 객체 소멸과정에서는 delete 연산자에 사용된 포인터 변수의 자료형에 상관없이 모든 소멸자가 호출되야함.
// 이를 위해서 소멸자에 virtual 선언을 추가해야한다.

// delete는 VDFirst 포인터에서 실행.
// 하지만 virtual 이므로, ~VDSecond가 호출

//~VDSecond가 실행되고, ~VDFirst가 실행됨.


