
//값에 의한 호출, 주소에 의한 호출


//주소
//#include<iostream>
//using namespace std;
//
//void swap(int* a, int* b) {
//	int tmp;
//	tmp = *a;
//	*a = *b;
//	*b = tmp;
//}
//
//
//int main() {
//	int x = 5, y = 10;
//	swap(&x, &y);
//	cout << x << ' ' << y;
//}





// 값에 의한 매개 변수의 생성자 실행과 호출
/*
#include<iostream>
using namespace std;

class Circle {
	int radius;
public:
	Circle();
	Circle(int r);
	~Circle();

	double getArea() { return 3.14 * radius * radius; }
	int getRadius() { return radius; }
	void setRadius(int radius) { this->radius = radius; }

};

Circle::Circle() {
	radius = 1;
	cout << "생성자 실행 radius= " << radius << endl;
}

Circle::Circle(int r) {
	radius = r;
	cout << "생성자 실행 radius= " << radius << endl;

}

Circle::~Circle() {
	cout << "소멸자 실행 radius" << radius << endl;
}

void increase(Circle c) { // 객체 c의 생성자가 실행이 되어야 하나 실행되지 않음
	int r = c.getRadius();
	c.setRadius(r + 1);
}//객체 c의 소멸자 실행



int main() {
	Circle waffle(30);
	increase(waffle); //내용이 그대로 복사
	cout << waffle.getRadius() << endl; //바뀌지 않았음
}
*/


//주소에 의한 호출
/*
#include<iostream>
using namespace std;

class Circle {
	int radius;
public:
	Circle();
	Circle(int r);
	~Circle();

	double getArea() { return 3.14 * radius * radius; }
	int getRadius() { return radius; }
	void setRadius(int radius) { this->radius = radius; }

};

Circle::Circle() {
	radius = 1;
	cout << "생성자 실행 radius= " << radius << endl;
}

Circle::Circle(int r) {
	radius = r;
	cout << "생성자 실행 radius= " << radius << endl;

}

Circle::~Circle() {
	cout << "소멸자 실행 radius" << radius << endl;
}

void increase(Circle *c) { // 객체 c의 생성자가 실행이 되어야 하나 실행되지 않음
	int r = c->getRadius();
	c->setRadius(r + 1);
}//객체 c의 소멸자 실행



int main() {
	Circle waffle(30);
	increase(&waffle); //내용이 그대로 복사
	cout << waffle.getRadius() << endl; //바뀌지 않았음
}

*/



/*

#include<iostream>

using namespace std;

class Circle {
	int radius;
public:
	Circle() { radius = 1; }
	Circle(int r) { radius = r; }
	double getArea() { return 3.14 * radius * radius; }
	void setRadius(int radius) { this->radius = radius; }

};

Circle getCircle() {
	Circle tmp(30);
	return tmp;
}


int main() {
	Circle c;
	cout << c.getArea() << endl;

	c = getCircle();
	cout << c.getArea() << endl;
}

*/



//참조는 변수공간을 새로 생성하는 것이 아니라, 그냥 이름만 달리하고 저장공간은 공유




/*
#include<iostream>
using namespace std;

int main() {
	cout << "i" << '\t' << "n" << '\t' << "refn" << endl;
	int i = 1;
	int n = 2;

	int& refn = n;

	n = 4;
	refn++;
	cout << i << '\t' << n << '\t' << refn << endl;


	refn = i;
	refn++;
	cout << i << '\t' << n << '\t' << refn << endl;

	int* p = &refn;
	*p = 20;
	cout << i << '\t' << n << '\t' << refn << endl;

}

*/








/*
#include<iostream>

using namespace std;

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int main() {
	int x = 1, y = 2;
	swap(x, y);
	cout << x << ' ' << y << endl;
}

*/



/*


#include<iostream>
using namespace std;

char& find(char s[], int index) {
	return s[index]; // s[index] 공간 참조
}

int main() {
	char name[] = "Mike";
	cout << name << endl;

	find(name, 0) = 'S'; // name[0]='S'
	cout << name << endl;

	char& ref = find(name, 2); //ref는 name[2]에 대한 참조
	ref = 't';
	cout << name << endl;
}


*/



//복사생성자
/*
class Circle{
	Circle(Circle &c);
}

Circle src(30);

Circle dest(src); => src객체를 복사하여 dest 객체를 생성하라.




#include<iostream>

using namespace std;

class Circle {
private:
	int radius;

public:
	Circle(Circle& c);
	Circle() { radius = 1; }
	Circle(int r) { radius = r; }
	double getArea() { return 3.14 * radius * radius; }
};

Circle::Circle(Circle& c) {
	this->radius = c.radius;
	cout << "복사 생성자 실행" << radius << endl;
}



int main() {
	Circle src(30);
	Circle dest(src);

	cout << "원본의 면적 = " << src.getArea() << endl;
	cout << "사본의 면적 = " << dest.getArea() << endl;

}

*/








