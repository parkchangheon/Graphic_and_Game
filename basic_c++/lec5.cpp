/*

#include<iostream>
using namespace std;

int big(int a, int b) {
	if (a > b)
		return a;
	else return b;

}

int big(int a[], int size) {
	int res = a[0];
	for (int i = 1; i < size; i++) {
		if (res < a[i])
			res = a[i];
		return res;
	}
}


int main() {
	int arr[5] = { 1,9,-2,8,6 };
	cout << big(2, 3) << endl;
	cout << big(arr, 5) << endl;
}

*/



/*
#include <iostream>
using namespace std;

// 원형 선언
void f(char c = ' ', int line = 1);

// 함수 구현
void f(char c, int line) {
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < 10; j++)
			cout << c;
		cout << endl;
	}
}

int main() {
	f(); // 한줄에 빈칸을 10개 출력한다.
	f('%'); // 한 줄에 '%'를 10개 출력한다.
	f('@', 5); // 5 줄에 '@' 문자를 10개 출력한다.
}





#include<iostream>
using namespace std;


class MyVector {
	int* p;
	int size;
public:
	MyVector(int n = 100) {
		p = new int[n];
		size = n;
	}
	~MyVector() { delete[] p; }
};

int main() {
	MyVector* v1, * v2;
	v1 = new MyVector();
	v2 = new MyVector(1024);
	cout << v1 << endl;
	cout << v2;


	delete v1;
	delete v2;
}






class Person {
public:
	double money;
	void addMoney(int money) {
		this->money += money;
	}

	static int sharedMoney;
	static void addShared(int n) {
		sharedMoney += n;
	}
};

int Person::sharedMoney = 10;
//static 객체는 프로그램과 생명을 같이한다.
//프로그램 생성시 멤버 생성
//객체가 생기기전에 이미 존재
// 객체가 사라져도 여전히 존재



//사용

Person lee;
lee.sharedMoney = 500;

*/



/*
#include <iostream>
using namespace std;

class Person {
public:
	double money; // 개인 소유의 돈
	void addMoney(int money) {
		this->money += money;
	}

	static int sharedMoney; // 공금
	static void addShared(int n) {
		sharedMoney += n;
	}
};

// static 변수 생성. 전역 공간에 생성
int Person::sharedMoney = 10;  // 10으로 초기화

// main() 함수
int main() {
	Person han;
	han.money = 100; // han의 개인 돈=100	
	han.sharedMoney = 200; // static 멤버 접근, 공금=200

	Person lee;
	lee.money = 150; // lee의 개인 돈=150
	lee.addMoney(200); // lee의 개인 돈=350
	lee.addShared(200); // static 멤버 접근, 공금=400

	cout << han.money << ' '
		<< lee.money << endl;
	cout << han.sharedMoney << ' '
		<< lee.sharedMoney << endl;
}
*/



/*
#include<iostream>
using namespace std;


class Math {
public:
	static int abs(int a) { return a > 0 ? a : -a; }
	static int max(int a, int b) { return a > b ? a : b; }
	static int min(int a, int b) { return a > b ? b : a; }
};

// Math 클래스를 만들고 전역함수들을 static 멤버로 캡슐화한 프로그램


int main() {
	cout << Math::abs(-5) << endl;
	cout << Math::max(10, 8) << endl;
	cout << Math::min(1, 8) << endl;
}
*/

//static 멤버 함수는 static 멤버만 접근 가능하다



