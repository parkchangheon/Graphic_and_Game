#include<iostream>
using namespace std;

// 한번 정해지면 절대 바뀌지 않을 값들
// constant => const (변수를 상수화 한다)
// const => 초기값을 지정해줘야한다.

const int AIR = 0;
const int STUN = 1;
const int POLYMORPH = 2;
const int INVINCIBLE = 3; //초기값을 지정해주어야함. (invincible에 대한 메모리가 할당되어있는게 아니라, 그냥 invincible이 들어오면, 컴파일러가 3으로 그냥 치환함)

// DATA 영역
// .data =>초기값이 없는 경우 
int a;
// .bss => 초기값이 있는 경우
int b = 2;
// .rodata => 읽기 전용 데이터
const char* msg = "Hello World";


int main()
{
	//스택영역 (esp, ebp)
	//const라고 해도, 함수내에 선언이 되면, 스택 메모리에 잡힌다.

	const int WHATEVER = 4;
}