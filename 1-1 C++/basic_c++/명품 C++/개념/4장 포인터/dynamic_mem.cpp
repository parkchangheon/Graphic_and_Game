//메모리 할당 및 반환

//메모리 할당.
//일반적으로는 프로그램 작성 단계에서 필요한 메모리를 확보하기 위해 변수, 객체, 배열을 정적으로 선언한다.
//그러나 실행 중에 필요한 만큼 메모리를 할당 받고 필요 없을때 반환하는 동적 메모리 할당 반환 메커니즘이 필요하다.

//new나 delete 연산자를 사용한다.

//동적 할당 => 힙영역에 저장됨.


//#include<iostream>
//using namespace std;
//
//int main()
//{
//	// 자료형 *포인터변수 = new 자료형
//	int* pInt = new int; 
//	char* pChar = new char;
//	//Circle* pCircle = new Circle();   클래스 타입의 객체할당.
//
//	delete pInt;
//	delete pChar;
//
//	//데이터 타입의 크기만큼 힙으로부터, 메모리를 할당받고 주소를 리턴한다.
//
//
//	int* p = new int;
//	if (!p) {
//		return;
//	}
//
//	*p = 5;
//	int n = *p;
//	delete p;
//
//
//	int* pInt = new int(2);  //2로 초기화된 int 공간 할당.
//	char* pchar = new char('a');


	// *********** 주의사항 ***************

	//delete로 메모리 반환시 적절하지 못한 포인터 사용시 실행 오류가 발생함.
	
	//int n;
	//int* p = &n;
	//delete p; //p는 동적할당을 받은게 아님.

	//int* p = new int;
	//delete p;
	//delete p; //중복 반환 불가.



//}

//#include<iostream>
//using namespace std;
//
//
//int main()
//{
//	int* p;
//	
//	p = new int;
//	if (!p){
//		cout << "메모리 할당 불가능.";
//		return 0;
//	}
//
//	*p = 5;
//	int n = *p;
//	cout << "*p = " << *p << endl;
//	cout << "n = " << *p << endl;
//
//	delete p;
//}

class Circle {
	int r;
public:
	Circle() {};
	Circle(int r) {};
};





// 배열의 동적 할당 및 반환
//자료형 *포인터변수 =  new 자료형[배열의 크기]
//delete[] 포인터변수
#include<iostream>
using namespace std;
int main() {

	////배열의 초기화는 불가능하다.
	////int* Array = new int[10](20);
	//int* Array = new int[] { 10, 20, 30, 40 }; //하지만 이와같이 초기화는 가능하다.

	//int *arr = new int[3];
	//if (!arr)
	//	return;

	//for (int i = 0; i < 3; i++) {
	//	cout << arr[i] << endl;
	//}

	//delete[] arr;

	Circle* ArrCircle = new Circle;   //생성자 Circle() 호출
	Circle* ArrCircle2 = new Circle(30); // 생성자 Cricle(30) 호출

	delete ArrCircle;
	delete ArrCircle2;


	
}