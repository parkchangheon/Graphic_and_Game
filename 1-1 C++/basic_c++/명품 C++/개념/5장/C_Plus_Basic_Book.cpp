//#include <iostream>
//
//
//void swap(int x, int y)
//{
//	int tmp;
//
//	tmp = x;
//	x = y;
//	y = tmp;
//}
//
//void swap2(int &x, int &y)
//{
//	int tmp;
//	tmp = x;
//	x = y;
//	y = tmp;
//}
//
//int main()
//{
//	int m = 2, n = 9;
//	swap(m, n);
//	std::cout << m << " " << n;
//	std::cout << std::endl;
//	swap2(m, n);
//	std::cout << m << " " << n;
//}





//#include<iostream>
//using namespace std;
//
//class Circle {
//private:
//	int radius;
//public:
//	Circle();
//	Circle(int r);
//	~Circle();
//	double getArea() { return 3.14 * radius * radius; }
//	int getRadius() { return radius; }
//	void setRadius(int radius) { this->radius = radius; }
//};
//
//
//Circle::Circle() {
//	radius = 1;
//	cout << "생성자 실행 radius = " << radius << endl;
//}
//
//Circle::Circle(int radius)
//{
//	this->radius = radius;
//	cout << "생성자 실행 radius = " << radius << endl;
//}
//
//Circle::~Circle() {
//	cout << "소멸자 실행 radius = " << radius << endl;
//}
//
//
//void increase(Circle c) {  //waffle 객체가 전달된 후 만일 객체 c의 생성자 Circle이 실행된다면, 객체 c의 반지름이 1로 초기화가 되어, 전달 받은 원본의 상태를 잃어버린다.
//	int r = c.getRadius();
//	c.setRadius(r + 1);
//}
//
//
//int main() {
//	Circle waffle(30);
//	increase(waffle);
//	cout << waffle.getRadius() << endl;
//}


//복사 생성자 
//값에 의한 호출시, 컴파일러는 매개 변수 객체의 생성자 대신 복사 생성자가 호출되도록 컴파일 한다.==> 그러기에 생성자가 실행되지 않는다.
//컴파일러는 클래스에 복사 생성자가 작성되어 있지 않는 경우 살인자 객체의 멤버 변수를 1:1로 매개변수 객체에 복사하는 디폴트 복사 생성자를 자동으로 삽입한다.



//주소에 의한 호출 과정

//#include<iostream>
//using namespace std;
//
//class Circle {
//	int radius;
//public:
//	Circle() { this->radius = 1; }
//	Circle(int r) { this->radius = r; }
//	int getRadius() { return this->radius; }
//	void setRadius(int r) { this->radius = r; }
//};
//
//void increase(Circle *c)
//{
//	int r = c->getRadius();
//	c->setRadius(r + 1);
//}
//
//int main()
//{
//	Circle waffle(30);
//	increase(&waffle);
//	cout << waffle.getRadius();
//}



//#include<iostream>
//using namespace std;
//
//class Circle {
//private:
//	int radius;
//
//public:
//	Circle() { this->radius = 1; }
//	Circle(int r) { this->radius = r; }
//	void setRadius(int radius) { this->radius = radius; }
//	double getArea() { return 3.14 * radius * radius; }
//	Circle getCircle() { ; }
//};
//
//Circle getCircle() {
//	Circle tmp(30);
//	return tmp;
//}
//
//int main()
//{
//	Circle c1(5);
//	Circle c2(30);
//	c1 = c2;
//
//	Circle c;
//	c=getCircle();
//
//	cout << c.getArea();
//}




//C++에서 참조는 다음과 같이 활용된다.
// 참조 변수
// 참조에 의한 호출
// 함수의 참조 리턴


//참조변수 
// 참조 변수는 이미 선언된 변수 (원본 변수로 지칭에 대한 별명으로서, 참조자&를 이용하여 선언)

//#include<iostream>
//using namespace std;
//
//class Circle {
//private:
//	int radius;
//
//public:
//	Circle() { this->radius = 1; }
//	Circle(int r) { this->radius = r; }
//	void setRadius(int radius) { this->radius = radius; }
//	double getArea() { return 3.14 * radius * radius; }
//	Circle getCircle() { ; }
//};
//
//int main() 
//{
//	//참조 변수는 따로 변수 공간을 가지지 않고, 각각 n과 circle을 공유한다.
//	int n = 2;
//	int& refn = n; // 참조 변수 refn 선언
//
//	Circle circle;
//	Circle& refc = circle; //참조 변수 refc 선언
//
//	refn = 3;
//	n = 5;
//	cout << refn << " " << n;
//	
//
//	refc.setRadius(30);
//	int* p = &refn; //포인터 p는 refn의 주소를 가진다. p는 n의 주소.
//	*p = 20; // n=20, refn=20;
//
//	//참조 변수 선언시 주의사항
//	int a = 2;
//	int& refa = a; //어떤 변수를 참조해야하는지 꼭 명시하기!!!!!!!!!!
//
//	//참조변수는 배열을 선언할 수 없다.
//}


//ex)
//#include<iostream>
//using namespace std;
//
//int main()
//{
//	cout << "i" << '\t' << "n" << '\t' << "refn" << endl;
//	int i = 1;
//	int n = 2;
//
//	int& refn = n;
//	n = 4;
//	refn++;
//	cout << i << '\t' << n << '\t' << refn << endl;  // 예상 1 5 5
//
//	refn = i; //여기서 refn = n 이고 refn=i을 선언하여, n까지 영향을 미침. refn++한 결과, 참조를 n에 하니, n 값이 변화
//	refn++;
//	cout << i << '\t' << n << '\t' << refn << endl;  // 예상 1 2 2
//
//	int* p = &refn;  //refn=n
//	*p = 20;
//	cout << i << '\t' << n << '\t' << refn << endl;  // 1 20 20
//}



//#include<iostream>
//using namespace std;
//
//class Circle {
//	int radius;
//public:
//	Circle() { radius = 1; }
//	Circle(int radius) { this->radius = radius; }
//	void setRadius(int radius) { this->radius = radius; }
//	double getArea() { return 3.14 * radius * radius; }
//};
//
//int main()
//{
//	Circle circle;
//	Circle& refc = circle;
//	refc.setRadius(10);
//	cout << refc.getArea() << " " << circle.getArea();
//}



//참조에 의한 호출
//#include<iostream>
//using namespace std;
//
////Swap의 a와 b는 공간을 할당받지 않는다.
//void swap(int& a, int& b) { // 참조로 호출한다. => 별명을 지어서 공간을 공유한다는 개념으로 접근하면 이해가 용이하다. 
//	int tmp;
//	tmp = a;
//	a = b;
//	b = tmp;
//}
//
//int main()
//{
//	int m = 2, n = 9;
//	swap(m, n);
//	cout << m << ' ' << n;
//}



//int average(int a[], int size, int &avg) {
//	if (size < 0)
//		return false;
//
//	int sum = 0;
//	for (int i = 0; i < size; i++)
//		sum += a[i];
//
//	avg = sum / size;
//	return true;
//}



//void readRadius(Circle& c) {
//	int r;
//	cout << "정수 값으로 반지름을 입력하세요";
//	cin >> r;
//	c.setRadius(r);
//}



//참조 리턴
//함수 리턴은 값만 된다. 하지만 c++에서는 함수가 참조를 리턴할 수 있다.

// // ex1)
//char c = 'a';
//
//char get() {
//	return c;
//}
//
//char a = get();
////get() = 'b';  ==>컴파일 오류
//
//
////ex2)
//char c = 'a';
//char& find() {
//	return c;
//}
//char a = find(); //a='a' 가된다.
//char& ref = find(); //ref는 c에 대한 참조
//ref = 'M' //c=M
//
//find() = 'b'; //find가 리턴한 공간에 'b' 문자 저장한다.
//



//#include<iostream>
//using namespace std;
//
//
//char& find(char s[], int index) //함수가 참조면 리턴값을 바꿔주는 것!!
//{
//	return s[index];
//}
//
//
//int main()
//{
//	char name[] = "MIKE";
//	cout << name << endl; //mike
//
//	find(name, 0) = 'S';
//	cout << name << endl; //sike
//
//	char& ref = find(name, 2);
//	ref = 't';
//	cout << name << endl; //site
//}



//#include<iostream>
//using namespace std;
//
////기본 타입, 포인터 변수, 참조 변수
////   a          *a          &a
//
//
//char c = 'a'; // a 값
//char* p = &c; // c의 주소를 가리키는 포인터 p
//char& s = c;  //c의 공간을 공유한다. (실질적으로 s가 가진 공간은 없다 => c 공간을 뺏어씀)
////*p = 'b';   //c값이 자체가 바뀜
////s = 'c';   //c값 자체 바뀜
//
//
//char& r() {
//	return c;
//}
//
//r() = 'c';  //변수 (리턴 c) 가 'c'로 변경
//
//char* p() { //주소리턴. 주소는 값이다.
//	return &c; //변수 c의 주소 리턴
//}
//
//
//char* s = p(); //s는 c의 주소를 저장
//*s = 'b';   //s가 가리키는 변수 c의 값이 'b'로 바뀜



//#include<iostream>
//using namespace std;
//
//int main()
//{
//	char c = 'a';
//	char* p = &c;
//	char& s = c;
//
//	*p = 'b';  //c가 b로 변한다.
//	s = 'c'; // c도 c가된다.
//}



//#include<iostream>
//using namespace std;
//
//void f(int a) { a = -a; }
//void g(int* a) { *a = -*a; }
//void h(int& a) { a = -a; }
//int main()
//{
//	int n = 5;
//	f(n);  // 안바뀐다.
//	cout << n << endl;
//	g(&n); // 주소를 보낸다. 
//	cout << n << endl;
//	h(n);  // 그냥 값을 보내는데, h 함수에서 n에 대한 별명만을 생성
//	cout << n << endl;
//
//}



//#include<iostream>
//using namespace std;
//
//int arr[] = { 0,1,3,5,7 };
//int& f(int n) {
//	return arr[n];
//}
//
//int main()
//{
//	f(0) = 100; 
//	cout << arr[0] << endl;
//	f(0) = f(1) + f(2) + f(3) + f(4);
//	cout << arr[0] << endl;
//
//	int& v = f(2);
//	v++;
//	cout << v<<endl;
//	cout << arr[2];
//}




//복사 생성자

//얕은 복사와 깊은 복사
//복사란 원본가 동일한 별개의 사본을 만드는 것.


//얕은 복사, 깊은 복사가 있다.
//얕은 복사에서는 메모리를 공유하는 문제를 가진다.  ==> 복사본을 변경할 시 원본도 변경된다.
// 가능한 얕은 복사는 하지 않는다.
//깊은 복사는 메모리도 복사를 해버린다.  ==> 

//class ClassName {
//	ClassName(ClassName& c);
//	//복사 생성자의 매개변수는 오직 하나이며, 자기 클래스에 대한 참조로 선언이 된다.
//	//오직 한개만 생성이 가능하다.
//};




//class Circle {
//	Circle(Circle &c); //복사생성자 생성
//};
//
//Circle::Circle(Circle& c) {
//
//}


//Circle src(30); ==> src 객체를 생성하는 일반 생성자
//Circle dest(src); ==> 객체 dest는 src를 복사하는 복사생성자


//Circle::Circle(Circle& c) {
//	this->radius = c.radius;
//}



//예제

//#include<iostream>
//using namespace std;
//
//class Circle {
//private:
//	int radius;
//public:
//	Circle(Circle& c);
//	Circle() { radius = 1; }
//	Circle(int radius) { this->radius = radius; }
//	double getArea() { return 3.14 * 3.14 * radius; }
//};
//
//Circle::Circle(Circle& c) {
//	this->radius = c.radius;
//	cout << "복사 생성자 실행되었다!";
//}
//
//int main()
//{
//	Circle src(30);
//	Circle dest(src);
//
//	cout << "원본의 면적" << src.getArea() << endl;
//	cout << "복사본의 면적" << dest.getArea() << endl;
//}




//만약 복사 생성자가 선언되어 있지 않더라도, 묵시적으로 디폴트 복사 생성자를 생성해주도록 컴파일 해준다.
//디폴트 복사 생성자 코드는 소위 얕은 복사를 실행하도록 만들어진 코드이다.
//모든 멤버를 일대일 사본에 복사하도록 구성이 된다.


//class Book {
//	double price;
//	int page;
//	char *title;
//	char *author;
//public:
//	Book(double pr, int p, char& t, char& a);
//	~Book();
//};
//
//
////컴파일러가 디폴트 복사생성자에 삽입하는 디폴트 복사 생성자는 
//Book(Book& book)
//{
//	this->price = book.price;
//	this->page = book.page;
//	this->title = book.title;
//	this->author = book.author;
//}


// 포인터 타입의 멤버 변수가 없는 클래스의 경우, 얕은 복사는 전혀 문제가 없다.
// 모든 멤버 변수 일대일 복사해도 공유의 문제가 발생하지 않는다.
//!!!!!!!!!!!!!!!! 그러나 클래스가 포인터 멤버 변수를 가지고 있는 경우, 원본 객체의 포인터 멤버 변수가 사본 객체의 포인터 멤버 변수에 복사되면 같은 메모리를 가리키게 되어 문제가 발생한다.


//얕은 복사 생성자 

//#include<iostream>
//#include<cstring>
//#pragma warning(disable:4996)
//using namespace std;
//
//class Person {
//	char* name;
//	int id;
//public:
//	Person(int id, const char* name);
//	~Person();
//	void changeName(const char* name);
//	void show() { cout << id << ',' << name << endl; }
//};
//
//
//
//Person::Person(int id, const char* name)
//{
//	this->id = id;
//	int len = strlen(name); //name의 문자 개수
//	this->name = new char[len + 1]; //name 문자열에 공간 할당
//	strcpy(this->name, name); //this->name에 name을 할당 (문자열 복사)
//}
//
//
//Person::~Person()
//{
//	if (name) //만일name이 동적할당이 되어있다면,
//		delete[] name;
//}
//
//void Person::changeName(const char* name) {
//	if (strlen(name) > strlen(this->name))
//		return;
//	strcpy(this->name, name);
//}
//
//int main()
//{
//	Person father(1, "Kitae");
//	Person daugther(father); //디폴트 복사생성자를 호출한다.
//
//	cout << "daugther 객체 생성 이후 =====" << endl;
//
//	father.show();
//	daugther.show();
//
//	daugther.changeName("Grace");
//	cout << " 딸의 이름을 바꾼 이후 ======" << endl;
//
//	cout << "daughter 이름을 Grace로 변경한 이후입니다. === " << endl;
//	father.show();
//	daugther.show();
//	//그냥 원래 있던 것들을 전부 복사 한다.
//
//	return 0;
//}



//여기서 얕은 복사의 문제점을 파헤쳐 보자면,
//Person::Person(Person& p) {
//	this->id = id;
//	this->name = p.name;
//}
//
//
//main 함수의 실행과정
//father 객체의 생성
//Person father(1, "Kitae");   //father 객체가 생성이 되고 id에 1이 설정되며, name 포인터에 char 배열이 동적 할당되고 Kitae로 초기화 된다.
//
//Person daughter(father);     //디폴트 복사 생성자를 컴파일러가 호출한다. ==>
//그래서 daugter는 1. Kitae를 보여준다. ==> 동일한 메모리를 가리킨다.
//
//
////그리고 Grace로 바뀌면, name은 메모리 공간을 공유하므로, father 객체 역시 Grace로 바뀐다.
//그리고 소멸자가 실행될때도 문제가 발생할 수 있다.
//father, Grace ~Grace, ~father 이다.
//그런데 메모리 공간을 grace가 먼저 반환하게 된다면, father으 이미 힙에 반환한 메모리를 또 반환하므로 실행시간 오류가 발생하고 프로그램이 비정상 종료된다.





//깊은 복사 생성자
//#include<iostream>
//#include<cstring>
//#pragma warning(disable:4996)
//using namespace std;
//
//class Person {
//	char* name;
//	int id;
//public:
//	Person(int id, const char* name);
//	Person(Person& person);
//	~Person();
//	void changeName(const char* name);
//	void show() { cout << id << ',' << name << endl; }
//};
//
//
//
//Person::Person(int id, const char* name)
//{
//	this->id = id;
//	int len = strlen(name); //name의 문자 개수
//	this->name = new char[len + 1]; //name 문자열에 공간 할당
//	strcpy(this->name, name); //this->name에 name을 할당 (문자열 복사)
//}
//
//Person::Person(Person& person)
//{
//	this->id = person.id;
//	int len = strlen(person.name);
//	this->name = new char[len + 1];
//	strcpy(this->name, person.name);
//	cout << "복사 생성자 실행. 원본 객체 이름 " << this->name << endl;
//}
//
//
//Person::~Person()
//{
//	if (name) //만일name이 동적할당이 되어있다면,
//		delete[] name;
//}
//
//void Person::changeName(const char* name) {
//	if (strlen(name) > strlen(this->name))
//		return;
//	strcpy(this->name, name);
//}
//
//int main()
//{
//	Person father(1, "Kitae");
//	Person daugther(father); //사용자 설정(깊은) 복사생성자를 호출한다.
//
//	cout << "daugther 객체 생성 이후 =====" << endl;
//
//	father.show();
//	daugther.show();
//
//	daugther.changeName("Grace");
//	cout << " 딸의 이름을 바꾼 이후 ======" << endl;
//	father.show();
//	daugther.show();
//	//그냥 원래 있던 것들을 전부 복사 한다.
//
//	return 0;
//}
//
//
//
//
//Person daugther(father); // 우리가 이런식으로 명시적으로 복사 생성자를 생성하기 때문에 인지가 가능하지만, 
//구현해놓지 않고 있다가 default 생성자가 실행되는 경우가 있다.
//
//
//묵시적 복사 생성의 경우는 3가지가 있는데,
//
//1. 객체로 초기화 되서 객체가 생성될때,
//Person son = father; //son 객체를 생성할때, father 객체로 초기화되도록 하는 선언문
//person son(father);  //컴파일러가 문장을 다음과 같이 변환하여 복사생성자를 호출한다.
//
//Person son;
//son = father 과 혼돈 x ==> 복사 생성자 호출되지 않음.
//
//
//
//2. 값에 의한 호출로 객체가 전달될때
//
//void f(Person person) { //매게 변수 person이 생성될때 복사 생성자 호출
//
//}
//
//person father(1, "Kitae");
//f(father); //값에 의한 호출로 father 객체 전달.
//// 값에 의한 호출로 매게 변수 객체가 생성될때, 생성자가 실행되지 않는다고 배웠다.
//==> 생성자 대신 복사 생성자가 실행된다. 복사생성자가 구현되지 않은 경우, 컴파일러가 삽입한 디폴트 복사 생성자가 실행된다.
//
//
//3. 함수가 객체를 리턴할때, 
//함수가 객체를 리턴할때, return 문은 리턴 객체의 복사본을 생성하여, 호출할 곳으로 전달한다.
//이때 복사 생성자가 호출된다.
//Person g() {
//	Person mother(2, "Jane");
//	return mother;
//}
//
//g(0);


//묵시적으로 복사생성자가 생성될때

//1. 객체로 초기화될때,
//2. 값에 의한 호출로 객체가 전달될떄,
//3. 함수가 객체를 리턴할때



//ex)

#include<iostream>
#include<cstring>
#pragma warning(disable:4996)
using namespace std;

class Person {
	char* name;
	int id;
public:
	Person(int id, const char* name);
	Person(Person& person);
	~Person();
	void changeName(const char* name);
	void show() { cout << id << ',' << name << endl; }
};



Person::Person(int id, const char* name)
{
	this->id = id;
	int len = strlen(name); //name의 문자 개수
	this->name = new char[len + 1]; //name 문자열에 공간 할당
	strcpy(this->name, name); //this->name에 name을 할당 (문자열 복사)
}

Person::Person(Person& person)
{
	this->id = person.id;
	int len = strlen(person.name);
	this->name = new char[len + 1];
	strcpy(this->name, person.name);
	cout << "복사 생성자 실행. 원본 객체 이름 " << this->name << endl;
}


Person::~Person()
{
	if (name) //만일name이 동적할당이 되어있다면,
		delete[] name;
}

void Person::changeName(const char* name) {
	if (strlen(name) > strlen(this->name))
		return;
	strcpy(this->name, name);
}

void f(Person person)   //값에 의한 호출로 객체가 전달될때. => person 객체의 복사생성자 호출
{
	person.changeName("dummy");
}


Person g() {
	Person mother(2, "Jane");
	return mother;     //함수에서 객체를 리턴할때, mother 객체의 복사본 생성. 복사본의 복사 생성자 호출
}


int main()
{
	Person father(1, "Kitae");
	Person son = father;  // 객체로 초기화되어 객체가 생성될때, son 객체의 복사 생성자가 호출된다.
	f(father);
	g();
}
