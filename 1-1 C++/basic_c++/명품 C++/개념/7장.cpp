/*
#include<iostream>
using namespace std;

class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick;
		this->punch = punch;
	}
	void show();
	Power operator+(Power op2);
	bool operator==(Power op2);

};

void Power::show() {
	cout << "kick= " << kick << ',' << "punch = " << punch << endl;
}

Power Power::operator+(Power op2) {
	Power tmp;
	tmp.kick = this->kick + op2.kick;
	tmp.punch = this->punch + op2.punch;
	return tmp;

}

bool Power::operator==(Power op2) {
	if (kick = op2.kick && punch == op2.punch)
		return true;
	else
		return false;
}


int main() {
	Power a(3, 5), b(4, 6), c;
	c = a + b;

	a.show();
	b.show();
	c.show();

	Power d(3, 5), e(3, 5);
	if (d == e)
		cout << "Same";
	else
		cout << "NOT SAME";
}

*/






/*

#include<iostream>
using namespace std;

class Power {
	int kick;
	int punch;

public:

	Power(int kick = 0, int punch = 0) {
		this->kick = kick;
		this->punch = punch;
	}
	void show();
	Power& operator+=(Power op2);

};


void Power::show() {
	cout << "kick = " << kick << ',' << "punch = " << punch << endl;
}

Power& Power::operator+=(Power op2) {
	kick = kick += op2.kick;
	punch = punch += op2.punch;
	return *this;
}

int main() {
	Power a(3, 5), b(2, 4), c;
	a.show();
	b.show();

	c = a += b;
	a.show();
	c.show();
}

*/





/*

#include<iostream>
using namespace std;

class Power {
	int kick;
	int punch;

public:

	Power(int kick = 0, int punch = 0) {
		this->kick = kick;
		this->punch = punch;
	}
	void show();
	Power& operator++();
};


void Power::show() {
	cout << "kick = " << kick << ',' << "punch = " << punch << endl;
}

Power& Power::operator++() {
	kick = kick++;
	punch = punch ++;
	return *this;
}

int main() {
	Power a(3, 5), b(2, 4), c;
	a.show();
	b.show();

	b = ++a; //++a하고 그것을 b 에 대입
	a.show();
	b.show();
}

*/




/*
#include<iostream>
using namespace std;

class Power {
	int kick;
	int punch;

public:

	Power(int kick = 0, int punch = 0) {
		this->kick = kick;
		this->punch = punch;
	}
	void show();
	Power& operator++(int x);
};


void Power::show() {
	cout << "kick = " << kick << ',' << "punch = " << punch << endl;
}

Power& Power::operator++(int x) {

	Power tmp = *this;
	kick++;
	punch++;
	return tmp;
}

int main() {
	Power a(3, 5), b;
	a.show();
	b.show();

	b = a++; 
	a.show();  //a는 증가됨
	b.show();  //b는 초기 a 그대로
}
*/




