//9-1

/*
#include<iostream>

using namespace std;

class Converter {
protected:
	double ratio;
	virtual double convert(double src) = 0;
	virtual string getSourceString() = 0;
	virtual string getDestString() = 0;

public:
	Converter(double ratio) { this->ratio = ratio; }
	void run() {
		double src;
		cout << getSourceString() << "을 " << getDestString() << "로 바꿉니다 ";
		cout << getSourceString() << "을 입력하세요 >>";
		cin >> src;
		cout << "변환 결과 : " << convert(src) <<"  "<< getDestString() << endl;
	}

};



class WonToDollar :public Converter {
public:
	WonToDollar(double a) : Converter(a) { ; }
	
	string getSourceString() {
		return "달러";
	}
	string getDestString() {
		return "원";
	}

	double convert(double w) {
		//달러를 원화로만 바꿈
		double result;
		result = w * ratio;
		return result;
	}
};

int main() {
	WonToDollar wd(1200);
	wd.run();
}

*/





//9-3
/*
#include<iostream>
using namespace std;

class LoopAdder {
	string name;
	int x, y, sum;
	void read();
	void write();

protected:
	LoopAdder(string name = "") {
		this->name = name;
	}
	int getX() { return x; }
	int getY() { return y; }
	virtual int calculate() = 0;
public:
	void run();
};


void LoopAdder::read() {
	cout << name << ":" << endl;
	cout << "처음 수에서 두번쨰 수까지 더합니다. 두수를 입력하세요 >> ";
	cin >> x >> y;
}

void LoopAdder::write() {
	cout << x << " 에서 " << y << "까지의 합 = " << sum << " 입니다" << endl;
}

void LoopAdder::run() {
	read();
	sum = calculate();
	write();
}


class ForLoopAdder :public LoopAdder {


public:
	ForLoopAdder(string s) { cout << s; }

	virtual int calculate() {

		int first = getX();  // 가상함수 안에 있어야 한다. 외부로 나가면 값이 달라짐.
		int second = getY();
		int result = 0;

		for (int i = first; i <= second; i++) {
			result+=i;
		}
		return result;
	}
};


int main() {
	ForLoopAdder forLoop("For Loop");
	forLoop.run();

}
*/



//9-5
/*
#include<iostream>
using namespace std;

class AbstractGate {
protected:
	bool x, y;
public:
	void set(bool x, bool y) { this->x; this->y = y; }
	virtual bool operation() = 0;
};

class ANDGate :public AbstractGate {
public:
	bool operation() {
		bool result;
		result = x && y;
		return result;
	}
};


class ORGate :public AbstractGate {
public:
	bool operation() {
		bool result;
		result = x || y;
		return result;
	}
};


class XORGate :public AbstractGate {
public:
	bool operation() {
		if(x!=y)
			return true;
		return false;
	}
};


int main() {
	ANDGate andGate;
	ORGate orGate;
	XORGate xorGate;

	andGate.set(true, false);
	orGate.set(true, false);
	xorGate.set(true, false);

	cout.setf(ios::boolalpha);
	cout << andGate.operation() << endl;
	cout << orGate.operation() << endl;
	cout << xorGate.operation() << endl;
}
*/





//9-6
/*
#include<iostream>
using namespace std;



class Abstract {
public:
	virtual bool push(int n) = 0;
	virtual bool pop(int& n) = 0;

	virtual int size() = 0;
};


class IntStack : public Abstract {
	int s, full,top;
	int* stack;
	

public:
	IntStack(int s = 5) {
		stack = new int[s];
		full = s;
		top = -1;
	}
	~IntStack() { delete[]stack; }
	virtual bool push(int n) {
		if (top == full) {
			return false;
		}
		else {
			++top;
			stack[top] = n;
			return true;
		}
	}

	virtual bool pop(int& n) {
		if (top == -1) {
			return false;
		}

		else {
			n = stack[top];
			top--;
			return true;
		}
	}

	virtual int size() {
		return top + 1;
	}
};


int main() {
	int c, pop;
	bool b;

	IntStack intstack(5);

	while (true) {
		cout << "1: push\t\t2: pop\t\t3: show_size\t\t4: exit\n선택하세요>> ";
		cin >> c;
		if (c == 1) {
			cout << "push 할 정수를 입력하세요>>";
			cin >> c;
			b = intstack.push(c);
			if (!b)
				cout << "stack is full...\n";
			else
				cout << "success!\n";
		}
		else if (c == 2) {
			b = intstack.pop(pop);
			if (!b)
				cout << "stack is empty...\n";
			else
				cout << "pop : " << pop << endl;
		}
		else if (c == 3)
			cout << "size : " << intstack.size() << endl;
		else
			break;
		cout << endl;
	}
}
*/



