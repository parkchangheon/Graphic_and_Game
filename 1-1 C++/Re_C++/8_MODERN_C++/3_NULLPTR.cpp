#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

class Knight
{

};

Knight* FindKnight()
{
	return nullptr;
}

void Test(int a)
{
	cout << "Test(int)" << endl;
}

void Test(void* ptr)
{
	cout << "Test(*)" << endl;
}

//NULLPTR을 만들어보자.

class NullPtr {
public:
	template<typename T>
	operator T* ()const //어떤 타입의 포인터와도 치환이 가능.
	{
		return 0;
	}

	template<typename C, typename T>
	operator T C::* ()const
	{
		return 0;
	}

private:
	void operator&() const; //주소값을 막는다.

};

const NullPtr _NullPtr;

int main()
{
	int* ptr = NULL; //define NULL 0
	Test(0);
	Test(NULL); // 이렇게 하면 둘다 int a 를 받는 함수를 호출한다.
	// NULL = 0 이므로
	Test(nullptr);

	auto knight = FindKnight();
	if ( knight == nullptr)
	{

	}

	return 0;

}