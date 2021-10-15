//8-6

//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//class BaseArray {
//private:
//	int capacity;
//	int* mem;
//
//protected:
//	BaseArray(int capacity = 100) {
//		this->capacity = capacity;
//		mem = new int[capacity];
//	}
//
//	~BaseArray() { delete[] mem; }
//
//	void put(int index, int val) { mem[index] = val; }
//	int get(int index) { return mem[index]; }
//	int getCapacity() { return capacity; }
//};
//
//
//
//class MyQueue :public BaseArray {
//	int front = 0;
//	int idx = 0;
//
//public:
//	MyQueue(int x) :BaseArray(x) { ; }
//
//	void enqueue(int a) {
//		idx++;
//		put(idx, a);
//		
//	}
//
//	int dequeue() {
//		if (idx < 0) {
//			exit(1);
//		}
//		++front;
//		idx--;
//		return get(front);
//		
//
//	}
//
//	int capacity() {
//		return getCapacity();
//	}
//
//	int length() {
//		return idx;
//	}
//};
//
//
//class MyStack : public BaseArray {
//	int top=0;
//public:
//	MyStack(int x) :BaseArray(x) { ; }
//
//	void push(int n) {
//		put(top,n);
//		top++;
//	}
//
//	int pop() {
//		top--;
//		int tmp = get(top);
//		return tmp;
//	}
//
//	int capacity() {
//		return getCapacity();
//	}
//
//	int length() {
//		return top;
//	}
//
//};
//
//
//int main() {
//
//	MyStack mStack(100);
//	int n;
//	cout << "스택에 삽입할 5개의 정수를 입력하라";
//	
//	for (int i = 0; i < 5; i++) {
//		cin >> n;
//		mStack.push(n);
//	}
//
//	cout << "스택용량:" << mStack.capacity() << ",스택크기:" << mStack.length() << endl;
//	cout << "스택의 모든 원소를 팝하여 출력한다.";
//	while (mStack.length() != 0) {
//		cout << mStack.pop() << ' ';
//	}
//	cout << endl << "스택의 현재 크기 :" << mStack.length() << endl;
//}







//8-7
/*
#include<iostream>
using namespace std;

class BaseMemory {
	char* mem;
protected:
	BaseMemory(int size) { mem = new char[size]; }
	~BaseMemory() { delete[] mem; }
	void setData(int index, char data) { mem[index] = data; }
	char getData(int index) { return mem[index]; }
};

class ROM :public BaseMemory {
	int length;
public:
	ROM(long size, char memory[], int len) : BaseMemory(size) {
		length = len;
		for (int i = 0; i < len; i++)
			setData(i, memory[i]);
	;}
	char read(int index) { return getData(index); }
};

class RAM :public BaseMemory {
public:
	RAM(int size):BaseMemory(size){ ; }
	void write(int index, int data) { setData(index, data); }
	char read(int index) { return getData(index); }
};


int main() {
	char x[5] = { 'h','e','l','l','o' };
	ROM biosROM(1024 * 10, x, 5);
	RAM mainMemory(1024 * 1024);

	for (int i = 0; i < 5; i++)
		mainMemory.write(i, biosROM.read(i));

	for (int i = 0; i < 5; i++)
		cout << mainMemory.read(i);
}


*/






//8-8

#include<iostream>
using namespace std;

class Printer {
	string model;
	string manufacturer;
	int printedCount;
	int availableCount;

protected:
	Printer(string model, string mnfc, int left) {
		this->model = model;
		this->manufacturer = mnfc;
		this->availableCount = left;
	}
	bool print(int pages) {
		if (availableCount < pages) {
			cout << "용지가 부족합니다";
			return false;
		}

		for (int i = 0; i < pages; i++) {
			availableCount--;
		}
		return true;

	};

	string getModel(){ return this->model; }
	string getManufacture() { return this->manufacturer; }
	int getAvailableCount() { return this->availableCount; }
};

class InkPrinter : Printer {
	int availableInk;
public:
	InkPrinter(string model, string mnfc, int left, int availableInk):Printer( model,  mnfc,  left){
		this->availableInk = availableInk;
	}
	void show() {
		cout << "잉크젯 : " << getModel() << " " << getManufacture() <<" 남은 종이 : "<< getAvailableCount() <<" 남은 잉크 "<< availableInk<<endl;
	}
	bool av_ink(int pages) {
		if (print(pages));
		else return false;

		if (availableInk < pages)
		{
			cout << "잉크부족"<<endl;
			return false;
		}
	
		for (int i = 0; i < pages; i++) {
			availableInk--;
		}
		return true;
		
	}

};

class LaserPrinter : Printer {
	int availabeToner;
public:
	LaserPrinter(string model, string mnfc, int left, int availabeToner) :Printer(model, mnfc, left) {
		this->availabeToner = availabeToner;
	}
	void show() {
		cout << "잉크젯 : " << getModel() << " " << getManufacture() <<" 남은 종이 : "<< getAvailableCount() <<" 남은 토너 "<< availabeToner<<endl;
	}

	bool av_toner(int pages) {
		if (print(pages));
		else  return false; 

		if (availabeToner < pages)
		{
			cout << "토너 부족"<<endl;
			return false;
		}

		for (int i = 0; i < pages; i++) {
			availabeToner--;
		}

		return true;
	}
};



int main() {
	InkPrinter* inkjet = new InkPrinter("officejet v40", "HP", 5, 10);
	LaserPrinter* laser = new LaserPrinter("SCX-6x45", "삼성전자", 3, 20);
	cout << "현재 작동 되는 프린터는 다음과 같다.\n";
	inkjet->show();
	laser->show();


	char select= 'y';

	while (select == 'y') {
		int type, n;
		cout << "(1: 잉크젯, 2:레이저)와 매수 입력 >> ";
		cin >> type >> n;
		if (type == 1) {
			if (inkjet->av_ink(n))
				cout << "프린트 하였습니다.\n";
		}

		else if (type == 2) {
			if (laser->av_toner(n))
				cout << "프린트하였습니다.\n";
		}
		inkjet->show();
		laser->show();

		cout << "계속 프린트하겠습니까?(y/n)";
		cin >> select;
		if (select == 'n')
			break;
		else if (select == 'y');
		else
			cout << "잘못입력";

	}

	delete inkjet;
	delete laser;



}