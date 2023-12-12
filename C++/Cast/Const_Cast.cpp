#include<iostream>
#include<stdio.h>

using namespace std;

//const_cast 
// const로 선언된 포인터만 const를 풀어줄 수 있다.
// 포인터가 아닌 일반 변수의 const는 풀어줄 수 없다.
// 함수 포인터, 멤버 함수에 대한 const는 풀어줄 수 없다.

int main()
{
	const int num = 10;
	const int* p = &num;

	int* p2 = const_cast<int*>(p);
	*p2 = 30;

	printf("&num = %x, p=%x, p2=%x \n", &num, p, p2);	//72eff7f4
	printf("num = %d, p=%d, p2=%d \n", num, *p, *p2);	//num = 10, p=30, p2=30

	// num, p, p2 모두 주소값은 똑같으나, 
	// 가리키는 값이 모두 다르다.

}