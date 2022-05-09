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




