/*
#include<iostream>
using namespace std;

class Account {
	string name;
	int number;
	int sum = 0;

public:
	Account(string s, int a, int b){
		this->name = s;
		this->number = a;
		this->sum = b;
	}

	void deposit(int money) {
		sum += money;
	}

	string getOwner() {
		return name;
	}

	int withdraw(int money) {
		sum -= money;
		return money;
	}

	int inquiry() {
		return sum;
	}

};

int main() {
	Account a("kitae", 1, 5000);
	a.deposit(50000);
	cout << a.getOwner() << "의 잔액은 " << a.inquiry() << endl;
	int money = a.withdraw(20000);
	cout << a.getOwner() << "의 잔액은 " << a.inquiry() << endl;
}

*/






/*
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

class Random {
public:

	int next() {
		return rand() % RAND_MAX;
		
	}

	int nextInRange(int a, int b) {
		return rand() % (b+1-a)+a;
	}
};

int main() {
	srand((unsigned)time(0));
	Random r;
	cout << "--0에서 " << RAND_MAX << "까지의 랜덤 정수 10개--" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.next();
		cout << n << ' ';
	}
	cout << endl << endl << "-- 2에서 " << "4까지의 랜덤 정수 10개 --" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.nextInRange(2, 4);
		cout << n << ' ';
	}
	cout << endl;
}
*/




/*
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

class EvenRandom {
public:

	int next() {
		int a;
		a = rand() % RAND_MAX;
		while (a % 2 == 1 || a == 0)
			a = rand() % RAND_MAX;
		return a;

	}

	int nextInRange(int a, int b) {
		int tmp = rand() % (b + 1 - a) + a;
		while (tmp % 2 == 1 || tmp == 0)
			tmp = rand() % (b + 1 - a) + a;
		return tmp;
	}
};

int main() {
	srand((unsigned)time(0));
	EvenRandom r;
	cout << "--0에서 " << RAND_MAX << "까지의 랜덤 정수 10개--" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.next();
		cout << n << ' ';
	}
	cout << endl << endl << "-- 2에서 " << "4까지의 랜덤 정수 10개 --" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.nextInRange(2, 4);
		cout << n << ' ';
	}
	cout << endl;
}
*/









/*
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

class SelectRandom {
public:
	int nextEvenInRange(int a=0, int b=RAND_MAX);
	int nextOddInRange(int a = 0, int b = RAND_MAX);
};

int SelectRandom::nextEvenInRange(int a, int b) {
	int tmp= rand() % (b + 1 - a) + a;
	while(tmp%2==1)
		tmp = rand() % (b + 1 - a) + a;
	return tmp;
}


int SelectRandom::nextOddInRange(int a, int b) {
	int tmp = rand() % (b + 1 - a) + a;
	while (tmp % 2 == 0)
		tmp = rand() % (b + 1 - a) + a;
	return tmp;
}



int main() {
	srand((unsigned)time(0));
	SelectRandom r;
	cout << "--0에서 " << RAND_MAX << "까지의 랜덤 정수 10개--" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.nextEvenInRange();
		cout << n << ' ';
	}
	cout << endl << endl << "-- 2에서 " << "4까지의 랜덤 정수 10개 --" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.nextOddInRange(2, 9);
		cout << n << ' ';
	}
	cout << endl;
}
*/






/*
#include<iostream>
using namespace std;

//선언부
class Oval {
int height, width;

public:
	Oval();
	Oval(int h, int w);
	~Oval();
	double getWidth();
	double getHeight();
	void set(int w, int h);
	void show();
};

//구현부
Oval::Oval() {
	this->height = this->width = 1;
}

Oval::Oval(int w, int h) {
	this->height = h;
	this->width = w;

}

Oval::~Oval() {
	cout <<"Oval 소멸 : width = "<< width << ", height = " << height<<endl;
}

double Oval::getWidth() {
	return this->width;
}

double Oval::getHeight() {
	return this->height;

}

void Oval::set(int w, int h) {
	this->width = w;
	this->height = h;
}

void Oval::show() {
	cout << "width = "<<width << " height = " << height << endl;
}



int main() {
	Oval a, b(3, 4);
	a.set(10, 20);
	a.show();
	cout << b.getWidth() << "," << b.getHeight() << endl;
}
*/



