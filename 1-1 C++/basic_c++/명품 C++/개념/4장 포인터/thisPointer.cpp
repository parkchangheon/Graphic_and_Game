//this pointer 


//this는 객체 자신에 대한 보인터이다.

//class Circle {
//	int radius;
//public:
//	Circle() { this->radius = 1; }
//	Circle(int radius) { this->radius = radius; }
//	void setRadius(int radius) { this->radius = radius; }
//};
//
//
////this와 객체의 관계를 보여준다.
//
//int main()
//{
//	Circle c1;
//	Circle c2(2);
//	Circle c3(3);
//
//	c1.setRadius(4);
//	c2.setRadius(5);
//}





//this는 클래스 멤버함수에서만 쓸 수 있다.
//멤버가 아닌 함수들은 쓸 수 가 없는데, 그 이유는 해당 함수들은 어디에도 속하지 않기 때문이다.

//멤버함수라도 static 함수이면 쓸 수 가 없는데, 그 이유는 정적 멤버 함수는 객체가 생성되기 전에 호출이 가능하다... 뒷장에 계속


//컴파일러가 this를 처리하는 방법

//class Sample {
//	int a;
//public:
//	void set(/*Sample* this,*/ int x) {   // 묵시적으로 포함되어있다.
//		this->a = x;
//	}
//};


