// C++_Class.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
/*
#include <iostream>
#include<string>
using namespace std;

int main() {
	string song("Falling in love with you");
	string elvis="Elvis Presley";
	string singer;

	cout << song + "를 부른 가수는";
	cout << "첫글자는 " << elvis[0] << " 이다"<<endl;
	getline(cin, singer);
	if (singer == elvis)
		cout << "맞았다" << endl;
	else
		cout << "WRONG!!";
}
*/



// 위임 생성자
/*
#include<iostream>
using namespace std;

class Circle {
public:
	int radius;
	Circle();
	Circle(int r);
	double getArea();
};


Circle::Circle() :Circle(1) {}

Circle::Circle(int r) {
	radius = r;
	cout << "반지름" << radius << "원 생성" << endl;
}

double Circle::getArea() {
	return 3.14 * radius * radius;
}



int main() {
	Circle donut;
	double area = donut.getArea();
	cout << " 도넛 면적은 " << area << endl;

	Circle pizza(30);
	area = pizza.getArea();
	cout << " 도넛 면적은 " << area << endl;

}

*/





//인라인 함수
// 짧은 코드의 함수를 계속호출하는 것은 비효율적이며 오버헤드 발생

//그러므로
/*
#include<iostream>
using namespace std;

inline int odd(int x) {
	return (x % 2);
}

int main() {
	int sum = 0;
	for (int i = 1; i <= 100; i++) {
		if (i % 2) //이것을 인라인 화
			sum += i;
	}
}
*/

// 실행시간이 빨라지나, 코드의 삽입으로 전체 코드 증가






//구조체를 쓰는 이유
// c언어와 호환성이 좋기 때문에


