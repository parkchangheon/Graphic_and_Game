//함수 중복
/*
#include<iostream>

using namespace std;

int big(int a, int b) {
	return (a > b ? a : b);
}

int big(int a[], int size) {
	int m=a[0];
	for (int i = 0; i < size; i++) {
		if (a[i] > m)
			m = a[i];
	}
	return m;
}

int main() {
	int arr[5] = { 1,2,99,2,4 };
	cout << big(2, 3) << endl;
	cout << big(arr, 5) << endl;
}

*/




//디폴트 매개변수
/*
#include<iostream>
#include<string>

using namespace std;

void star(int a = 5);
void msg(int id, string text = " ");

void star(int a) {
	for (int i = 0; i < a; i++)
		cout << '*';
	cout << endl;
}

void msg(int id, string text) {
	cout << id << ' ' << text << endl;
}

int main() {
	star();
	star(10);

	msg(10);
	msg(10, "Hello");
}
*/


//포인터의 경우, 
//void f(int* p = NULL);
//void g(int x[] = NULL);
//void h(*s = "Hello");

//와 같이 표현이 가능하다.



//함수 중복 예제2)
/*
#include<iostream>

using namespace std;

void printer(char ch = '*', int num = 10) {
	for (int i = 0; i < num; i++) {
		cout << ch;
	}
	cout << endl;
}

int main() {
	printer();
	printer('%');
	printer('&', 20);
}
*/




// 생성자에서의 중복
/*
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
	~MyVector() { delete[]p; }
};


int main() {
	MyVector* v1, * v2;
	v1 = new MyVector(); // 디폴트 정수 배열 100 동적 할당.
	v2 = new MyVector(200); // 정수 배열 200 동적 할당.

	delete v1;
	delete v2;

}
*/





//중복 함수의 모호성
//1. 매개변수 형의 모호성 
//2. 참조 매개변수의 모호성
//3. 디폴트 매개변수의 모호성

//1.
//float al(float a);
//float ar(double a);



//2. 
/*
#include<iostream>

using namespace std;

int add(int a, int b) {
	return a + b;
}

int add(int a, int& b) {
	b = b + a;
	return b;
}

int main() {
	int s = 10, t = 20;
	cout << add(s, t); // 모호하다!
}

*/



//3. 
/*
#include<iostream>
#include<string>

using namespace std;

void msg(int id) {
	cout << id << endl;
}


void msg(int id, string s = "") {
	cout << id << ":" << s << endl;
}

int main() {
	msg(5,"goodmorning"); //정상적 컴파일
	msg(6);// 어디로 가야할지 모호함

}
*/





//static!!!
//static은 해당 클래스의 모든 객체를 연결하는 개념으로 생각!
/*
#include<iostream>
using namespace std;;

class person {
public:
	double money;
	void addMoney(int money) {
		this->money += money;
	}

	//static으로 표현된 멤버변수/함수들은 person객체들이 공유하는 공금으로 표현. 
	// 위의 money는 객체는 개인이 소유한 돈을 표현.

	static int sharedMoney;
	static void addShared(int n) {
		sharedMoney += n;
	}
};


//static 멤버 변수는 외부에 전역 변수로 선언되어야 한다.
int person::sharedMoney = 10;// 이렇게 변수를 클래스 밖에 선언을 해줌.

int main() {
	person han;
	han.money = 100; //개인돈 100
	han.sharedMoney = 200; // 공금 200

	person lee;
	lee.money=150;
	lee.addMoney(200); //개인돈 350
	lee.addShared(200); // 공금 400

	cout << han.money << lee.money << endl;
	cout << han.sharedMoney << lee.sharedMoney << endl;
	// person::sharedMoney로 접근해도 똑같다.
}
*/





/*
#include<iostream>
using namespace std;;

class person {
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


int person::sharedMoney = 10;

int main() {
	person::addShared(50);
	cout << person::sharedMoney << endl;

	person han;
	han.money = 100;
	han.sharedMoney = 200;
	person::sharedMoney = 300;
	person::addShared(100);

	cout << han.money << ' ' << person::sharedMoney << endl;
}
*/



//static의 캡슐화

// 전역변수와 전역함수를 선언하지 말고 클래스에 static 멤버로 선언하면서 캡슐화를 시키도록한다.
/*
#include<iostream>
using namespace std;

class Math {
public:
	static int abs(int a) { return a > 0 ? a : -a; }
	static int max(int a, int b) { return a > b ? a : b; }
	static int min(int a, int b) { return a > b ? b : a; }
};

int main() {
	cout << Math::abs(-5) << endl;
	cout << Math::max(10, 8) << endl;
	cout << Math::min(10, 8) << endl;
}

*/




//static 멤버를 공유의 목적으로 사용하는 예
/*
#include<iostream>

using namespace std;

class Circle {
private:
	static int numOfCirlce;
	int radius;

public:
	Circle(int r = 1);
	~Circle() { numOfCirlce--; }
	double getArea() { return 3.14 * radius * radius; }
	static int getNumOfCircle() { return numOfCirlce; }
};

Circle::Circle(int r) {
	radius = r;
	numOfCirlce++;
}


int Circle::numOfCirlce = 0;      // 0으로 초기화해준다.


int main() {
	Circle* p = new Circle[10];
	cout << "생존하고 있는 원의 갯수 = " << Circle::getNumOfCircle() << endl;

	delete[]p;
	cout << "생존하고 있는 원의 갯수 = " << Circle::getNumOfCircle() << endl;

	Circle a;
	cout << "생존하고 있는 원의 갯수 = " << Circle::getNumOfCircle() << endl;

	Circle b;
	cout << "생존하고 있는 원의 갯수 = " << Circle::getNumOfCircle() << endl;
}
*/


// 10 0 1 2




//static 함수는 static 멤버 변수에 접근 하거나  static 함수만 호출가능.
//ex_
/*
class person {
public:
	double money;
	static int sharedmoney;

	int total() {                   // non-static 함수는 static이나 non-static 멤버에 모두 접근이 가능하다.
		return money + sharedmoney;
	}
};




class person {
public:
	double money;
	static int sharedMoney;

	static void addShared(int n) {
		this->sharedMoney += n;  // thos를 사용하면 컴파일 오류가 난다.
	}
};

*/