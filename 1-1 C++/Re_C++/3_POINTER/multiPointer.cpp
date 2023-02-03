#include<iostream>
using namespace std;

//다중 포인터 
//써야하는 이유

void SetMessage(const char* a)
{
	a = "Bye";
}

void SetMessage(const char** a)
{
	
}

int main()
{
	const char* msg = "Hello";
	SetMessage(msg);
	cout << msg;

	const char** pp = &msg;
	SetMessage(pp);
	*pp = "Bye";
	cout << msg << endl;
}