//7-1
/*
#include<iostream>
using namespace std;

class Book {
	string title;
	int price, pages;
public:
	Book(string title = "", int price = 0, int pages = 0) {
		this->title = title; this->price = price; this->pages = pages;
	}

	void show() {
		cout << title << ' ' << price << "원" << pages << "페이지" << endl;
	}
	string getTitle() { return title; }


	friend Book operator +=(Book& op1, int a); // friend로 구현
	Book& operator-=(int a); // 클래스 멤버 함수로 구현  
	// 연산자 중복은 새로운 Book으로 갱신하기 때문에 리턴 타입을 
};

Book operator +=(Book& op1, int a) {
	Book tmp;
	op1.price = op1.price + a;
	return op1;
}

Book& Book::operator-=(int a) {
	price = price - a;
	return *this;
}


int main() {

	Book a("청춘", 20000, 300), b("미래", 30000, 500);
	a += 500;
	b -= 500;

	a.show();
	b.show();
}

*/





//7-2
/*
#include<iostream>
using namespace std;


class Book {
	string title;
	int price, pages;
public:
	Book(string title = "", int price = 0, int pages = 0) {
		this->title = title; this->price = price; this->pages = pages;
	}

	void show() {
		cout << title << ' ' << price << "원" << pages << "페이지" << endl;
	}
	string getTitle() { return title; }

	friend bool operator ==(Book op1,int a);
	bool operator==(string s);
	bool operator==(Book& op1);
};

bool operator==(Book op1, int a) {
	if (op1.price == a)
		return true;
	return false;
}


bool Book::operator==(string s) {
	if (this->title == s)
		return true;
	return false;
}

bool Book::operator==(Book& op1) {
	if (this->title == op1.title && this->price == op1.price && this->pages == op1.pages)
		return true;
	return false;
}

int main() {
	Book a("명품 C++", 30000, 500), b("고품 C++", 30000, 500);
	if (a == 30000) 
		cout << "정가 30000원" << endl;

	if (a == "명품 C++") 
		cout << "명품 C++ 입니다." << endl;

	if (a == b) 
		cout << "두책이 같은 책입니다." << endl;

}

*/




/*
//7-3

#include<iostream>
using namespace std;


class Book {
	string title;
	int price, pages;
public:
	Book(string title = "", int price = 0, int pages = 0) {
		this->title = title; this->price = price; this->pages = pages;
	}

	void show() {
		cout << title << ' ' << price << "원" << pages << "페이지" << endl;
	}
	string getTitle() { return title; }

	friend bool operator!(Book& a);
};

bool operator!(Book& a) {
	if (a.price == 0)
		return true;
	return false;
}



int main(){
	Book book("벼룩시장", 0, 50);
	if (!book)
		cout << "공짜다" << endl;
}

*/



/*
//7-4

#include<iostream>
#include<string>
using namespace std;


class Book {
	string title;
	int price, pages;
public:
	Book(string title = "", int price = 0, int pages = 0) {
		this->title = title; this->price = price; this->pages = pages;
	}

	void show() {
		cout << title << ' ' << price << "원" << pages << "페이지" << endl;
	}
	string getTitle() { return title; }

	friend bool operator<(string s, Book& a);
};


bool operator<(string s, Book& a) {
	if (s < a.title)
		return true;
	return false;
}


int main() {
	Book a("청춘", 20000, 300);
	string b;
	cout << "책 이름을 입력하세요 >>";
	getline(cin, b);

	if (b < a)
		cout << a.getTitle() << "이" << b << "보다 뒤에 있구나!" << endl;

}

*/



//7-5
/*
#include<iostream>
using namespace std;

class Color {
	int r, g, b;

public:
	Color(){ this->r = 0, this->g = 0, this->b = 0; }
	Color(int r, int g, int b) { this->r = r, this->g = g, this->b = b; }

	friend Color& operator+(Color a, Color b);
	friend bool operator==(Color a,Color b);
	void show();
};

Color& operator+(Color a, Color b) {
	Color tmp;
	tmp.r = a.r + b.r;
	tmp.g = a.g + b.g;
	tmp.b = a.b + b.b;

	return tmp;
}

bool operator==(Color a, Color b) {
	if (a.r == b.r && a.g == b.g && a.b == b.b)
		return true;
	return false;
}

void Color::show() {
	cout << r << " " << g << " " << b<< endl;
}


int main() {
	Color red(255, 0, 0), blue(0, 0, 255), c;
	c = red + blue;
	c.show();

	Color fuchsia(255, 0, 255);
	if (c == fuchsia)
		cout << "보라색 맞음";
	else
		cout << "보라색 아님";
}
*/




//7-6 ****
/*
#include<iostream>
using namespace std;

class Matrix {
	int num[4];
public:
	Matrix() { ; }
	Matrix(int a, int b, int c, int d) {
		num[0] = a; num[1] = b; num[2] = c; num[3] = d;
	};
	Matrix operator+(Matrix b);
	friend void operator+=(Matrix& a,Matrix& b);
	bool operator==(Matrix b);
	void show() { cout << num[0] << num[1] << num[2] << num[3] << endl; }
};

Matrix Matrix::operator+(Matrix b) {
	Matrix tmp;
	for (int i = 0; i < 4; i++) {
		tmp.num[i] = this->num[i] + b.num[i];
	}
	return tmp;
}


void operator+=(Matrix& a,Matrix& b) {
	for (int i = 0; i < 4; i++)
		a.num[i] += b.num[i];

}

bool Matrix::operator==(Matrix b) {
	for (int i = 0; i < 4; i++) {
		if (this->num[i] == b.num[i]);
		else return false;
	}
	return true;
}



int main() {
	Matrix a(1, 2, 3, 4), b(2, 3, 4, 5), c;
	c = a + b;
	a += b;
	a.show(); b.show(); c.show();
	if (a == c)
		cout << "a and c are the same" << endl;
}


*/




//7-7
/*
#include<iostream>

using namespace  std;

class Matrix {
	int num[4];

public:
	Matrix() { ; }
	Matrix(int a, int b, int c, int d) {
		num[0] = a; num[1] = b; num[2] = c; num[3] = d;
	}

	void operator>>(int arr[]);
	friend void operator<<(Matrix& a, int arr[]);
	void show() {
		for (int i = 0; i < 4; i++)
			cout << num[i];
	}

};

void Matrix::operator>>(int arr[]) {
	for (int i = 0; i < 4; i++)
		arr[i] = this->num[i];
}

void operator<<(Matrix& a, int arr[]) {
	for (int i = 0; i < 4; i++) {
		a.num[i] = arr[i];
	}
}

int main() {
	Matrix a(4, 3, 2, 1), b;
	int x[4], y[4] = { 1,2,3,4 };
	a >> x;
	b << y;

	for (int i = 0; i < 4; i++)
		cout << x[i] << ' ';
	cout << endl;
	b.show();
}


*/




//7-8
/*
#include<iostream>

using namespace std;

class Circle {
	int radius;
public:
	Circle(int radius = 0) { this->radius = radius; }
	void show() { cout << "radius = " << radius << "인 원" << endl; }
	friend Circle& operator++(Circle& c);
	friend Circle operator++(Circle& c, int x);
};

Circle& operator++(Circle& c) {
	c.radius++;
	return c;
}//++a

Circle operator++(Circle& c, int x) {
	Circle test = c;
	c.radius++;
	return test;
} //b=a++

int main() {
	Circle a(5), b(4);
	++a;
	b = a++;
	a.show();
	b.show();

}

*/



//7-9

/*
#include<iostream>

using namespace std;

class Circle {
	int radius;
public:
	Circle(int radius = 0) { this->radius = radius; }
	void show() { cout << "radius = " << radius << "인 원" << endl; }
	friend Circle operator+(int x, Circle c);
};


Circle operator+(int x, Circle c) {
	Circle t;
	t.radius = x + c.radius;
	return t;
}

int main() {
	Circle a(5), b(4);
	b = 1 + a;
	a.show();
	b.show();

}

*/



//7-10

/*
#include<iostream>
using namespace std;

class Statics {
	int* arr;
	int cnt;
public:
	Statics() { arr = new int[8]; cnt = 0; }
	bool operator!();

	Statics& operator<<(int a);
	void operator~();
	int operator>>(int& a);
	~Statics() { delete[] arr; }
};

bool Statics::operator!() {
	if (this->arr && this->cnt==0)
		return true;
	return false;
}

Statics& Statics::operator<<(int a){
	this->arr[cnt] = a;
	cnt++;
	return *this;
}

void Statics::operator~() {
	for (int i = 0; i <cnt; i++)
		cout << arr[i]<<' ';
}

int Statics::operator>>(int& a) {
	a = 0;
	for (int i = 0; i < cnt; i++)
		a += this->arr[i];
	return a /= cnt;
}

int main() {
	Statics stat;
	if (!stat)
		cout << "현재 통계 데이터가 없습니다." << endl;

	int x[5];
	cout << "5개의 정수를 입력하라>>";
	for (int i = 0; i < 5; i++)
		cin >> x[i];

	for (int i = 0; i < 5; i++)
		stat << x[i];

	stat << 100 << 200;
	~stat;

	int avg;
	stat >> avg;
	cout << "avg=" << avg << endl;

}

*/





//7-11
/*
#include<iostream>
using namespace std;

class Stack {
	int stack[10];
	int top;
public:
	Stack() { top = 0; }
	Stack& operator<<(int a);
	bool operator!();
	Stack operator>>(int &x);
};

Stack& Stack::operator<<(int a) {
	stack[top] = a;
	top++;
	return *this;
}

bool Stack :: operator!() {
	if (top == 0)
		return true;
	return false;
}

Stack Stack::operator>>(int& x) {
	x = stack[top - 1];
	top--;
	return *this;
}


int main() {
	Stack stack;
	stack << 3 << 5 << 10;

	while (true) {
		if (!stack)
			break;
		int x;
		stack >> x;
		cout << x << ' ';
	}
	cout << endl;
}
*/




//7-12

