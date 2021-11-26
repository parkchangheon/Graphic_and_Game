//#include<iostream>
//using namespace std;
//
//
//template <class T>
//void myswap(T& a, T& b) {
//	T tmp;
//	tmp = a;
//	a = b;
//	b = tmp;
//}
//
//
//int main() {
//	int a = 5, b = 10;
//	myswap(a, b);
//
//	cout << a << " " << b;
//}

//template는 템플릿을 선언하고, 제네릭 타입을 선언하는 키워드를 써준뒤 제네릭 타입을 선언한다.
// template < class T >


/*
#include<iostream>
using namespace std;

class Circle {
	int radius;
public :
	Circle(int radius = 1) { this->radius = radius; }
	int getRadius() { return radius; }
};


template <class T>
void myswap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

int main() {
	int a = 4, b = 5;
	myswap(a, b);
	cout << a << "\t" << b << endl;

	double c = 10, d = 20;
	myswap(c, d);
	cout << c << "\t" << d << endl;

	Circle donut, pizza(5);
	myswap(donut, pizza);

	cout << donut.getRadius() << "\t" << pizza.getRadius() << endl;

}
*/

/*
#include<iostream>
using namespace std;

template<class T>
T add(T data[], int n) {
	T sum = 0;
	for (int i = 0; i < n; i++) {
		sum += data[i];
	}
	return sum;
}


int main()
{
	int x[] = { 1,2,3,4,5 };
	double d[] = { 1.2, 2.3, 3.4, 4.5, 5.6, 6.7 };

	cout << "x = " << add(x, sizeof(x)/sizeof(x[0])) << endl;
	cout << "x = " << add(d, sizeof(d) / sizeof(d[0])) << endl;
}

*/

//#include<iostream>
//using namespace std;
//
//template <class T>
//class MyStack {
//	int tos;
//	T data[100];
//
//public:
//	MyStack();
//	void push(T element);
//	T pop();
//};
//
//template <class T>
//void MyStack<T>::push(T element) {
//
//}
//
//template <class T> 
//T MyStack<T>::pop() {
//
//}
//
//template <class T>
//MyStack<T>::MyStack(){
//
//}
//
//int main() {
//	MyStack<int> iStack;
//
//}




/*
#include<iostream>
using namespace std;

template <class T>
class MyStack {
	int tos;//top of stack
	T data[100];

public:
	MyStack();
	void push(T element);
	T pop();
};

template<class T>
MyStack<T>::MyStack() {
	tos = -1;
}

template<class T>
void MyStack<T>::push(T element) {
	if (tos == 99)
	{
		cout << "Stack is Full";
		return;
	}
	tos += 1;
	data[tos] = element;
}

template<class T>
T MyStack<T>::pop() {
	T retData;
	if (tos == -1)
	{
		cout << "Stack is Empty";
		return 0;
	}
	retData = data[tos--];
	return retData;
}

int main() {
	MyStack<int> iStack;
	iStack.push(3);
	cout << iStack.pop() << endl;

	MyStack<double> dStack;
	dStack.push(3.5);
	cout << dStack.pop() << endl;

	MyStack <char>* p = new MyStack<char>(); //동적할당.
	p->push('A');
	cout << p->pop() << endl;
	delete p;
}

*/




/*
#include<iostream>
#include<string>

using namespace std;

template <class T>
class MyStack {
	int tos;//top of stack
	T data[100];

public:
	MyStack();
	void push(T element);
	T pop();
};

template<class T>
MyStack<T>::MyStack() {
	tos = -1;
}

template<class T>
void MyStack<T>::push(T element) {
	if (tos == 99)
	{
		cout << "Stack is Full";
		return;
	}
	tos += 1;
	data[tos] = element;
}

template<class T>
T MyStack<T>::pop() {
	T retData;
	if (tos == -1)
	{
		cout << "Stack is Empty";
		return 0;
	}
	retData = data[tos--];
	return retData;
}

class Point {
	int x, y;
public:
	Point(int x = 0, int y = 0) { 
		this->x = x; this->y = y; 
	}

	void show() { 
		cout << '(' << x << ',' << ')' << endl; 
	}
};

int main() {
	MyStack<int*> ipStack;   //int*을 저장하는 스택
	int* p = new int[3];

	for (int i = 0; i < 3; i++)
		p[i] = i * 10;

	ipStack.push(p);
	int* q = ipStack.pop();

	for (int i = 0; i < 3; i++)
		cout << q[i] << ' ';

	cout << endl;
	delete[] p;



	MyStack<Point> pointStack;   //Point 객체만 저장하는 스택
	Point a(2, 3), b;
	pointStack.push(a);
	b = pointStack.pop();
	b.show();

	MyStack<Point*> pStack;
	pStack.push(new Point(20, 30)); // 동적생성
	Point* pPoint = pStack.pop();
	pPoint->show();

	MyStack<string> stringStack;
	string s = "C++";
	stringStack.push(s);
	stringStack.push("java");

	cout << stringStack.pop() << ' ';
	cout << stringStack.pop() << endl;

}
*/






//#include<iostream>
//using namespace std;
//
//template <class T1, class T2>
//class GClass {
//	T1 data1;
//	T2 data2;
//
//public:
//	GClass();
//	void set(T1 a, T2 b);
//	void get(T1& a, T2& b);
//};
//
//
//template<class T1,class T2>
//GClass<T1, T2>::GClass() {
//	data1 = 0;
//	data2 = 0;
//}
//
//
//template<class T1, class T2>
//void GClass<T1, T2>::set(T1 a, T2 b) {
//	data1 = a;
//	data2 = b;
//}
//
//template<class T1, class T2>
//void GClass<T1, T2>::get(T1& a, T2& b) {
//	a = data1;
//	b = data2;
//}
//
//int main() {
//	int a;
//	double b;
//	GClass<int, double> x;
//
//	x.set(2, 0.5);
//	x.get(a, b);
//	cout << "a=" << a << '\t' << "b=" << b << endl;
//
//	char c;
//	float d;
//	GClass<char, float> y;
//	y.set('m', 12.5);
//	y.get(c, d);
//	cout << "c=" << c << '\t' << "d=" << d << endl;
//
//}


//#include<iostream>
//#include<vector>
//
//using namespace std;
//
//int main() {
//	vector<int> v;
//
//	v.push_back(3);
//	v.push_back(5);
//	v.push_back(10);
//
//	int a=v.at(2);
//	cout << a <<endl;
//	v[2] = 11;
//	a = v.at(2);
//	cout << a << endl;
//
//
//	vector<int>::iterator it;
//	it = v.begin();   // it는 벡터 v의 첫번째 원소를 가리킨다.
//	it = v.erase(it); // erase는 v에서 it 번째 원소를 삭제한다.
//
//	int s = v.size();
//	int c = v.capacity();
//	cout << s <<endl;
//	cout << c << endl;
//}



//#include<iostream>
//#include<vector>
//using namespace std;
//
//int main() {
//	vector<int> v;
//	v.push_back(1);
//	v.push_back(2);
//	v.push_back(3);
//
//	vector<int>::iterator it;   //벡터 v의 원소에 대한 포인터 it 선언
//
//	for (it = v.begin(); it != v.end(); it++) {
//		int n = *it;  //it가 가리키는 원소 값 리턴
//		n = n * 2;    // 2배
//		*it = n;      //it가 가리키는 원소에 값쓰기
//	}
//
//	for (it = v.begin(); it != v.end(); it++)
//		cout << *it << ' ';
//	cout << endl;
//}



//#include<iostream>
//#include<map>
//using namespace std;
//
//int main() {
//	map<string, string>dic;
//
//	//저장하는 방법
//	dic.insert(make_pair("love", "사랑")); // "love" , "사랑" 저장
//	dic["mad"] = "화남";
//	dic["eng"] = "영어";
//	dic["jap"] = "일어";
//
//	string kor = dic["mad"];
//	string eng = dic["eng"];
//	string jap = dic["jap"];
//
//	cout << dic.size() << endl;
//
//	if (dic.find(eng) == dic.end())   // eng의 키를 찾지 못하면 조건문은 true
//		cout << "found" << endl;
//
//	cout << kor;
//}


/*
#include<iostream>
#include<string>
#include<map>
using namespace std;

int main() {
	map<string, string> dic;

	//단어 저장하기.
	dic.insert(make_pair("love", "사랑"));
	dic.insert(make_pair("apple", "사과"));
	dic["cherry"] = "체리";

	cout << "저장된 단어의 갯수 : " << dic.size() << endl;
	string eng;
	while (true) {
		cout << "찾고 싶은 단어 >>";
		getline(cin, eng);

		if (eng == "exit")
			break;

		if (dic.find(eng) == dic.end())//eng의 키를 끝까지 찾았는데 없음.
			cout << "없음" << endl;
		else
			cout << dic[eng] << endl;
	}

	cout << "종료합니다." << endl;

}
*/
