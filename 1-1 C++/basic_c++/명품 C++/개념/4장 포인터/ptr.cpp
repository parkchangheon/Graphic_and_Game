#include<iostream>
using namespace std;

class Circle {
private:
	int radius;
public:
	Circle() { this->radius = 1; }
	Circle(int r) { this->radius = r; }
	void setArea(int r)
	{
		this->radius = r;
	}

	double getArea() {
		return 3.14 * radius * radius;
	}
	double getArea(int r) {
		return 3.14 * r * r;
	}
};

class Sample {
	int a;
public:
	Sample() { a = 100; cout << a << ' '; }
	Sample(int x) { a = x; cout << a << ' ';}
	Sample(int x, int y) { a = x * y; cout << a << ' ';}
	int get() { return a; }
};

int main()
{
	Circle donut;
	Circle* p;
	p = &donut;

	donut.getArea();
	p->getArea();

	Circle circleArray[3];
	circleArray[0].setArea(10);
	circleArray[2].setArea(30);

	for (int i = 0; i < 3; i++)
	{
		cout << circleArray[i].getArea() << endl;
	}

	p = circleArray;
	for (int i = 0; i < 3; i++) {
		cout << p->getArea() << endl;
		p++;
	}

	//ÃÊ±âÈ­
	Circle circleArr[3] = { Circle(10),Circle(20),Circle(30) };

	Circle circles[2][3];
	circles[0][0].setArea(1);
	circles[0][1].setArea(2);
	circles[0][2].setArea(3);
	circles[1][0].setArea(4);
	circles[1][1].setArea(5);
	circles[1][2].setArea(6);

	//or 

	Circle circles2[2][3] = { {Circle(1),Circle(2),Circle(3)},
								{Circle(1),Circle(2),Circle(3)} };


	Sample arr[3];
	Sample arr2D[2][2] = { {Sample(2,3),Sample(2,4)},{Sample(5),Sample()} };
}