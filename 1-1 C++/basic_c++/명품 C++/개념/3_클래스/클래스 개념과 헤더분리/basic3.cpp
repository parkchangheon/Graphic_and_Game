
//객체 만들기 1 
/*
#include<iostream>

using namespace std;

class Circle { 
public:
	int radius;
	double getArea();
}; // 클래스 선언부

double Circle::getArea() {
	return 3.14 * radius * radius;
} // 클래스 구현부 




int main() {
	Circle pizza;
	pizza.radius = 3;
	double area = pizza.getArea();
	cout << "피자의 면적은 : " << area << endl;

	Circle donut;
	donut.radius = 1;
	area = donut.getArea();
	cout << "피자의 면적은 : " << area << endl;

}

*/


//ex
/*
#include<iostream>

using namespace std;

class Rectangle {
public:
	int height, width;
	int RectArea();
};

int Rectangle::RectArea() {
	return height * width;
}

int main() {
	Rectangle r;
	r.width = 10;
	r.height = 20;

	cout << r.RectArea();
}
*/




//생성자
/*
#include<iostream>

using namespace std;


class Circle {
public:
	int radius;
	double getArea();
	Circle();
	Circle(int r);
};

Circle::Circle() {
	radius = 1;
	cout << "반지름 " << radius << " 원 생성" << endl;
}

Circle::Circle(int r) {
	radius = r;
	cout << "반지름 " << radius << " 원 생성" << endl;
}


double Circle::getArea() {
	return 3.14 * radius * radius;
}



int main() {
	Circle donut;
	double area = donut.getArea();
	cout << "도넛 면적은 " << area << endl;

	cout << endl;

	Circle pizza(30);
	area = pizza.getArea();
	cout << "pizza 면적은 " << area << endl;
}
*/





//위임 생성자 사용 
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
	cout << "도넛 면적은 " << area << endl;

	cout << endl;

	Circle pizza(30);
	area = pizza.getArea();
	cout << "pizza 면적은 " << area << endl;
}

*/



//위임 생성자 활용

/*
class Point {
	int x, y;

public :
	Point();
	Point(int a, int b);
};


Point::Point() {
	x = 0, y = 0;
}

Point::Point(int a, int b) {
	x = a, y = b;
}




#include<iostream>

using namespace std;


class Point {
	int x, y;
public :
	Point();
	Point(int a, int b);

	void show() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};


Point::Point():Point(0,0){}
Point::Point(int a, int b) :x(a),y(b){}



int main() {
	Point origin;
	Point target(10, 20);
	origin.show();
	target.show();
}




#include<iostream>

using namespace std;

class Circle {
public:
	int radius;
	Circle();
	Circle(int r);
	~Circle();

	double getArea();
};


Circle::Circle() {
	radius = 1;
	cout << "반지름" << radius << "원 생성" << endl;
}

Circle::Circle(int r) {
	radius = r;
	cout << "반지름" << radius << "원 생성" << endl;
}


Circle::~Circle() {
	cout << "반지름" << radius << "원 소멸" << endl;
}


double Circle::getArea() {
	return 3.14 * radius * radius;
}

int main() {
	Circle donut;
	double area = donut.getArea();
	cout << "도넛 면적은 " << area << endl;

	cout << endl;

	Circle pizza(30);
	area = pizza.getArea();
	cout << "pizza 면적은 " << area << endl;
	cout << endl;
}

*/




//인라인 자동 처리 
/*
#include<iostream>
using namespace std;


class Circle {
	int radius;
public:
	Circle() {
		radius = 1;
	}// 인라인 자동처리 
	Circle(int r);
	double getArea() {
		return 3.14 * radius * radius; // 인라인 자동처리
	}
};

Circle::Circle(int r) {
	radius = r;
}
*/



//구조체
/*
#include<iostream>

using namespace std;

struct StructCircle {
private:
	int radius;
public:
	StructCircle(int r) {
		radius = r;
	}
	double getArea();
};

double StructCircle::getArea() {
	return 3.14 * radius * radius;
}


int main() {
	StructCircle waffle(3);
	cout << "면적은" << waffle.getArea();
}



#include<iostream>
using namespace std;

#include "Circle.h"

int main() {
	Circle donut;
	double area = donut.getArea();
	cout << "도넛 면적은 " << area << endl;

	cout << endl;

	Circle pizza(30);
	area = pizza.getArea();
	cout << "pizza 면적은 " << area << endl;
	cout << endl;
}







*/
