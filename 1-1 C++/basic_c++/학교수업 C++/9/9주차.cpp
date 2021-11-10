#include<iostream>
using namespace std;


class SortedArray; //¼±¾ð

class SortedArray {
	int size;
	int* p;
	void sort();

public: 
	SortedArray();
	SortedArray(SortedArray& src);
	SortedArray(int p[], int size);
	~SortedArray();

	SortedArray operator + (SortedArray& op2);
	SortedArray& operator = (const SortedArray& op2);
	void show();
};

SortedArray::SortedArray(){
	p = NULL;
	size = 0;
}

SortedArray::SortedArray(SortedArray& src) {
	this->size = src.size;
	this->p = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		this->p[i] = src.p[i];
	}
}

SortedArray::SortedArray(int p[], int size) {
	this->p = new int[size];
	this->size = size;
	for (int i = 0; i < size; i++) {
		this->p[i] = p[i];
	}
}

SortedArray::~SortedArray() {
	delete []p;
}

SortedArray SortedArray::operator+ (SortedArray& op2) {
	SortedArray op1;
	op1.size = this->size + op2.size;
	op1.p = new int[op1.size];

	for (int i = 0; i < op1.size; i++) {
		if (i < this->size)
			op1.p[i] = this->p[i];
		else
			op1.p[i] = op2.p[i - (op1.size - op2.size)];
	}
	return op1;
}

SortedArray& SortedArray::operator=(const SortedArray& op2) {
	delete[] p;
	this->size = op2.size;
	this->p = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		this->p[i] = op2.p[i];
	}
	return *this;
}

void SortedArray::sort() {
	int tmp;
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (p[i] < p[j]||p[i]==p[j]);
			else
			{
				tmp = p[j];
				p[j] = p[i];
				p[i] = tmp;
			}
		}
	}
}

void SortedArray::show() {
	sort();
	for (int i = 0; i <size; i++) {
		cout << p[i] << ' ';
	}
	cout << "\n";
}



int main() {
	int n[] = { 2,20,6 };
	int m[] = { 10,7,8,30 };
	SortedArray a(n, 3), b(m, 4), c;

	c = a + b;

	a.show();
	b.show();
	c.show();
	cout << endl;


}