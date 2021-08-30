//9-7

/*
#include<iostream>
using namespace std;

class Shape {
protected:
	string name;
	int width, height;

public:
	Shape(string n = "", int w = 0, int h = 0) {
		name = n;
		width = w; 
		height = h;
	}

	virtual double getArea() { return 0; }
	string getName() { return name; }
};


class Oval : public Shape {
public:
	Oval(string n, int a, int b) :Shape(n, a, b) { ; }
	double getArea() {
		return 3.14 * width * height;
	}
};


class Rect : public Shape {
public:
	Rect(string n, int a, int b) :Shape(n, a, b) { ; }
	double getArea() {
		return  width * height;
	}
};

class Triangular : public Shape {
public:
	Triangular(string n, int a, int b) :Shape(n, a, b) { ; }
	double getArea() {
		return  width * height*0.5;
	}
};


int main() {
	Shape* p[3];
	p[0] = new Oval("빈대떡", 10, 20);
	p[1] = new Rect("찰떡", 30, 40);
	p[2] = new Triangular("토스트", 30, 40);

	for (int i = 0; i < 3; i++)
		cout << p[i]->getName() << " 넓이는 " << p[i]->getArea() << endl;
	for (int i = 0;i < 3; i++)
		delete p[i];
}
*/





//9-9

/*
#include<iostream>
using namespace std;

class Printer {
protected:
	string model;
	string manufacturer;
	int printedCount;
	int availableCount;
public:
	Printer(string model, string manufacturer, int availableCount) {
		this->model = model, this->manufacturer = manufacturer,  this->availableCount = availableCount;
	}

	virtual void print(int pages) = 0;
	virtual void show() = 0;
};


class InkPrinter :public Printer {
	int availableInk;

public:
	InkPrinter(string model, string manufacturer, int availableCount, int availableInk) :Printer(model, manufacturer, availableCount) 
	{ this->availableInk=availableInk;}
	

	void print(int pages) {
		if (availableInk < pages || availableCount < pages)
			cout << "용지나 잉크가 부족합니다 " << endl;
		else {
			availableInk -= pages;
			availableCount -= pages;
		}
	}

	void show() {
		cout << "잉크 : " << model << ", " << manufacturer << ", 남은종이 " << availableCount << ", 남은 잉크 " << availableInk << endl;
	}
};



class LaserPrinter :public Printer {
	int availableToner;

public:
	LaserPrinter(string model, string manufacturer, int availableCount, int availableToner) :Printer(model, manufacturer, availableCount)
	{
		this->availableToner = availableToner;
	}


	void print(int pages) {
		if (availableToner < pages || availableCount < pages)
			cout << "용지나 잉크가 부족합니다 " << endl;
		else {
			availableToner -= pages;
			availableCount -= pages;
		}
	}

	void show() {
		cout << "레이저 : " << model << ", " << manufacturer << ", 남은종이 " << availableCount << ", 남은 토너 " << availableToner << endl;
	}
}; 



int main() {
	Printer *ip;
	Printer *lp;
	char c='y';
	ip = new InkPrinter("Officejet V40", "HP", 5, 10);
	lp = new LaserPrinter("SCX-6x45", "삼성전자", 3, 20);

	cout << "현재 작동중인 2대의 프린터는 아래와 같다."<<endl;
	ip->show();
	lp->show();

	while (c == 'y') {
		int select, paper;
		cout << "프린터(1 : 잉크젯, 2: 레이저)와 매수 입력 >> ";
		cin >> select >> paper;

		if (select == 1) {
			ip->print(paper);
		}


		else if (select == 2) {
			lp->print(paper);

		}

		else {
			cout << " 잘못된 입력입니다. ";
			continue;
		}


		ip->show();
		lp->show();

		cout << "계속 프린트 하시겠습니까? (y/n) >> ";
		cin >> c;


	}


}
*/


