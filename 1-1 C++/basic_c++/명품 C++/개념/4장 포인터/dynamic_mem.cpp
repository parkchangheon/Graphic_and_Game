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

//class Circle {
//	int r;
//public:
//	Circle() {};
//	Circle(int r) {};
//};





//// 배열의 동적 할당 및 반환
////자료형 *포인터변수 =  new 자료형[배열의 크기]
////delete[] 포인터변수
//#include<iostream>
//using namespace std;
//int main() {
//
//	////배열의 초기화는 불가능하다.
//	////int* Array = new int[10](20);
//	//int* Array = new int[] { 10, 20, 30, 40 }; //하지만 이와같이 초기화는 가능하다.
//
//	//int *arr = new int[3];
//	//if (!arr)
//	//	return;
//
//	//for (int i = 0; i < 3; i++) {
//	//	cout << arr[i] << endl;
//	//}
//
//	//delete[] arr;
//
//	Circle* ArrCircle = new Circle;   //생성자 Circle() 호출
//	Circle* ArrCircle2 = new Circle(30); // 생성자 Cricle(30) 호출
//
//	delete ArrCircle;
//	delete ArrCircle2;
//
//
//	
//}



//#include<iostream>
//using namespace std;
//
//class Circle {
//public:
//	Circle() {};
//	Circle(int r) {};
//};
//
//int main()
//{
//	Circle* p = new Circle;
//	Circle* q = new Circle(30);
//
//	delete p;
//	delete q;
//
//}



#include<iostream>
using namespace std;

class Circle {
	int radius;

public:
	Circle();
	Circle(int r);
	~Circle();
	void setRadius(int r) { radius = r; }
	double getArea() { return 3.14 * radius * radius; }
};

Circle::Circle() {
	radius = 1;
	cout << "생성자 실행 radius = " << radius << endl;
}


Circle::Circle(int r) {
	this->radius = r;
	cout << "생성자 실행 radius = " << radius << endl;
}

Circle::~Circle()
{
	cout << "소멸자 실행 radius = " << radius << endl;
}
//
//
//
//int main()
//{
//	int radius;
//	while (true) {
//		cout << "정수 반지름 입력(음수이면 종료) >> ";
//		cin >> radius;
//		if (radius < 0)
//			break;
//		Circle* p = new Circle(radius);
//		cout << "원의 면적은 = " << p->getArea() << endl;
//		delete p;
//	}
//}




//int main() {
//	Circle* pArray = new Circle[3];
//	Circle* pBrray = new Circle[]{Circle(3), Circle(2), Circle(1)};
//
//	for (int i = 0; i < 3; i++)
//		cout << pBrray[i].getArea() << endl;
//
//	Circle* p = pBrray;
//	for (int i = 0; i < 3; i++)
//	{
//		cout << p->getArea() << endl;
//		p++;
//	}
//	delete[]pBrray;
//}


//메모리 누수에 관하여

//int main()
//{
//	char n = 'a';
//	char* p = new char[1024];
//	p = &n;
//	//이렇게 된다면, new로 할당 받은 1024바이트는 메모리 누수가 발생한다.
//	//p가 처음에는 할당받은 1024바이트를 n을 받게되면서 잃어버려 반환할 수 없게 된다.
//
//	for (int i = 0; i < 1000000; i++)
//	{
//		p = new char[1024];
//	}
//}


