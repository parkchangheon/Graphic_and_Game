//8-1

//#include<iostream>
//using namespace std;
//
//class Circle {
//	int radius;
//public:
//	Circle(int radius = 0) { this->radius = radius; }
//	int getRadius() { return radius; }
//	void setRadius(int radius) { this->radius = radius; }
//	double getArea() { return 3.14 * radius * radius; }
//};
//
//
//class NameCircle:public Circle {
//	string str;
//public:
//	NameCircle() {};
//	NameCircle(int a, string s) {
//		setRadius(a);
//		str = s;
//	}
//	void show() { cout << "반지름이 " << getRadius() << "인 " << str; }
//
//};
//
//int main() {
//	NameCircle waffle(3, "waffle");
//	waffle.show();
//}







//8-2

//#include<iostream>
//using namespace std;
//
//
//class Circle {
//	int radius;
//public:
//	Circle(int radius = 0) { this->radius = radius; }
//	int getRadius() { return radius; }
//	void setRadius(int radius) { this->radius = radius; }
//	double getArea() { return 3.14 * radius * radius; }
//};
//
//class NameCircle :public Circle {
//	string name;
//public:
//	void setName(string s) { this->name = s; }
//	string getName() { return name; }
//};
//
//int main() {
//	NameCircle pizza[5];
//	int max = 0;
//	int index = 0;
//
//	cout << "5개의 정수 반지름과 원의 이름을 입력하세요" << endl;
//	for (int i = 0; i < 5; i++) {
//		int a; 
//		string s;
//
//		cout << i+1 << ">>";
//		cin >> a >> s;
//		pizza[i].setRadius(a);
//		pizza[i].setName(s);
//
//	}
//
//	for (int i = 0; i < 5; i++) {
//		if (max < pizza[i].getArea()) {
//			max = pizza[i].getArea();
//			index = i;
//		}
//	}
//
//	cout << "가장 면적이 큰 피자는 " << pizza[index].getName();
//
//}



//8-3~4
//#include<iostream>
//using namespace std;
//
//
//class Point {
//	int x, y;
//public:
//	Point(int x=0, int y=0) { this->x = x; this->y = y; }
//	int getX() { return x; }
//	int getY() { return y; }
//
//protected:
//	void move(int x, int y) { this->x = x; this->y = y; }
//};
//
//
//class ColorPoint: public Point {
//	string color;
//public:
//	ColorPoint(int x, int y, string s) {
//		Point(x, y);
//		this->color = s;
//	}
//	void setPoint(int x, int y) { move(x, y); }
//	void setColor(string c) { this->color = c; }
//	
//	void show() { cout << color << "색으로 " << "(" << getX()<<"," << getY() << ")" << "에 위치한 점입니다."<<endl; }
//};
//
//int main() {
//	ColorPoint cp(5, 5, "RED");
//	cp.show();
//
//	cp.setPoint(10, 20);
//	cp.setColor("BLUE");
//	cp.show();
//}






//8-5

//#include<iostream>
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
//int main() {
//	MyQueue mQ(100);
//	int n;
//
//	cout << "큐에 삽입할 정수 5개를 입력하라>>";
//	for (int i = 0; i < 5; i++) {
//		cin >> n;
//		mQ.enqueue(n);
//	}
//
//	cout << "큐의 용량 : " << mQ.capacity() << ", 큐의 크기:" << mQ.length() << endl;
//	cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";
//
//	while (mQ.length() != 0) {
//		cout << mQ.dequeue() << ' ';
//	}
//	cout << endl << "큐의 현재 크기: " << mQ.length() << endl;
//}


