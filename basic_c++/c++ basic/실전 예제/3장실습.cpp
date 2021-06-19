//3-1
/*
#include<iostream>
using namespace std;

class Tower {
	int height;
public:
	Tower();
	Tower(int h);
	int getHeight();
};

Tower::Tower() {
	height = 1;
}

Tower::Tower(int h) {
	height = h;
}

int Tower::getHeight() {
	return height;
}


int main() {
	Tower myTower;
	Tower seoulTower(100);
	cout << "높이는 " << myTower.getHeight() << "미터" << endl;
	cout << "높이는 " << seoulTower.getHeight() << "미터" << endl;
}
*/




//3-2
/*
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Date {
	int year, month, day;
public:
	Date(int y, int m, int d);
	Date(string s);
	void show();
	int getyear() { return year; };
	int getmonth() { return month; };
	int getday() { return day; };
};

Date::Date(int y, int m, int d) {
	this->year = y;
	this->month = m;
	this->day = d;
}

Date::Date(string s) {
	int spt;
	this->year = stoi(s);

	spt = s.find('/');
	this->month = stoi(s.substr(spt + 1));
	
	spt = s.find('/', spt + 1);
	this->day = stoi(s.substr(spt + 1));
}

void Date::show() {
	cout << year << "년" << month << "월" << day << "일"<<endl;
}


int main() {
	Date birth(2014, 3, 20);
	Date independenceday("1945/8/15");
	independenceday.show();
	cout << birth.getyear() << ',' << birth.getmonth() << ',' << birth.getday() << endl;
}
*/




//3-3
/*
#include<iostream>
#include<cstring>
using namespace std;

class Account {
	string name;
	int num, total;

public:
	Account(string s, int n, int t);
	int deposit(int m);
	int withdraw(int m);
	string getOwner();
	int inquiry();

};

Account::Account(string s, int n, int t) {
	this->name = s;
	this->num = n;
	this->total = t;
}

int Account::deposit(int m) {
	this->total = this->total +m;
	return this->total;
}

int Account::withdraw(int m) {
	this->total = this->total - m;
	return this->total;
}

string Account::getOwner() {
	return this->name;
}

int Account::inquiry() {
	return this->total;
}

int main() {
	Account a("kitae", 1, 5000);
	a.deposit(50000);
	cout << a.getOwner() << "의 잔액은" << a.inquiry() << endl;
	int money = a.withdraw(20000);
	cout << a.getOwner() << "의 잔액은" << a.inquiry() << endl;

}

*/

////////////////////////////06-18

//3-4
/*
#include<iostream>
using namespace std;


class CoffeeMachine {
	int coffee, water, sugar;

public:

	CoffeeMachine(int a, int b, int c);
	void drinkEspresso();
	void drinkAmericano();
	void drinkSugarCoffee();
	void fill();
	void show();
};

CoffeeMachine::CoffeeMachine(int a, int b, int c) {
	this->coffee = a;
	this->water = b;
	this->sugar = c;
}

void CoffeeMachine::drinkEspresso() {
	coffee -= 1;
	water -= 1;
}

void CoffeeMachine::drinkAmericano() {
	coffee -= 1;
	water -= 2;
}

void CoffeeMachine::drinkSugarCoffee() {
	coffee -= 1;
	water -= 2;
	sugar -= 1;
}

void CoffeeMachine::show() {
	cout << "커피 머신 상태, " << "커피:" << this->coffee << " 물:" << this->water << " 설탕:" << this->sugar<<endl;
}

void CoffeeMachine::fill() {
	this->coffee = 10;
	this->water = 10;
	this->sugar = 10;
}


int main() {
	CoffeeMachine java(5, 10, 3);
	java.drinkEspresso();
	java.show();
	java.fill();
	java.show();
}

*/



//3-5
/*
#include<iostream>
#include<cstdlib>
#include<ctime>


using namespace std;

class Random {

public:
	int next();
	int nextInRange(int a, int b);
};


int Random::next() {
	//srand((unsigned)time(0));
	int n = rand();
	return n;
}

int Random::nextInRange(int a, int b) {
	//srand((unsigned)time(0));
	int n = rand()%(b-a+1)+a;
	return n;
}

int main() {
	Random r;
	cout << "--0에서"<< RAND_MAX << "까지의 랜덤 정수 10개 --" << endl;

	for (int i = 0; i < 10; i++) {
		int n = r.next();
		cout << n << ' ';
	}
	cout << endl << endl << "--2에서" << "4 까지의 랜덤 정수 10개-- " << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.nextInRange(2, 4);
		cout << n << ' ';
	}
	cout << endl;

}
*/



//3-6
/*
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;


class EvenRandom {
	int seed = 0;
public:
	int Even();
};


int EvenRandom::Even() {
	int n;

	do {
		n = rand();
	} while (n % 2 == 1);

	return n;
}

int main() {
	EvenRandom er;
	cout<<er.Even();
}

*/




//3-8
/*
#include<iostream>
#include<string>
using namespace std;

class Integer {
	int n;
public:
	int get();
	int isEven();
	void set(int a);

	Integer(int a);
	Integer(string c);

};
Integer::Integer(int a) {
	this->n = a;
}

Integer::Integer(string c) {
	this->n = stoi(c);
}

int Integer::get() {
	return this->n;
}

int Integer::isEven() {
	if (n % 2 == 0) {
		return n;
	}
}

void Integer::set(int a) {

}

int main() {
	Integer n(30);
	cout << n.get() << ' ';

	n.set(50);
	cout << n.get() << ' ';

	Integer m('300');
	cout << m.get() << ' ';
	cout << m.isEven();


}


*/

