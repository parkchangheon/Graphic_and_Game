//1) RTTI

/*
run time type information의 약자로 프로그램 실행중에 개체의 형식이 결정될 수 있도록 하는 매커니즘이다.

실행중에 포인터가 가리키는 객체의 타입을 알 수 있게 해주는 방법이라고 보면 된다.


A타입에서 B타입으로 변경할때 정보가 필요하다.
컴파일 시간에 타입 변환이 이루어지면 굳이 RTTI가 필요없다.
컴파일 단계에서 충분히 알 수 있고 특정 타입으로 확정할 수 있기 때문이다.

일반적인 상속 관계에서 발생하는 타입관계는 대부분 컴파일 시간에 해석되지만, 
virtual 클래스로 상속받는 경우에는 컴파일 시간에 추적이 불가능하다.
==>> 왜?? 

virtual 클래스로부터 상속이 하나라도 존재하면 RTTI를 사용하고 있다고 보면됨.

dynamic_cast의 경우 RTTI에 의존적인데 초기단계 분석에서는 static_cast 분석을 사용하고, 불가능하면 RTTI를 사용하는 구조로 설계되었다.

하지만 dynamic_cast를 사용한다고 해서 모두 RTTI와 직접 연결되는것은 아니다.
RTTI와 다중 상속은 크게 관련이 없다. 오히려 RTTI와 가상 상속이 직접적인 관계가 존재한다.
*/

#include <iostream>

class Base {};
class MAN : public Base {};
class WOMAN : public Base {};

int main()
{
	Base* base_m = new MAN();
	Base* base_w = new WOMAN();
	return 0;
}

//이러한 코드가 존재한다고 가정하자.

/*
 RTTI가 없던 시절에는 base_m이나 base_w가 런타임에서 어떤 하위 클래스를 가르키고 있는지 알 수 없다.
 RTTI는 다형성을 가진 클래스 즉, C++ 기준에서 가상함수가 존재하는 클래스에서 사용할 수 있으며, 
 그에 대한 이유는 RTTI 정보가 가상함수 테이블인 vtable 에 첫번째 요소에 type_info를 참조하는 주소를 저장하기 때문이다. 
 그래서 가상함수가 사용된 클래에 한해서만 정보가 유지된다.
 이에 대한 비용으로 type_info가 객체 메모리에 추가되어 vtable의 저장 공간이 소모된다.
RTTI는 일반적인 클래스 객체에 두게되면 C와의 하위호환성을 포기해야 한다.
C의 구조체와 C++의 클래스 객체는 바이너리 호환성을 지니기 때문에 C에서 클래스 객체에 접근이 가능한데, C++ 클래스가 멤버중 virtual 선언된 멤버를 가지게 되면 그 멤버에는 접근이 불가능해진다.
RTTI의 제약인 다형성에 대한 테스트를 해보자.
*/


#include <iostream>

class Base { void C() {} };
class MAN : public Base { void A() {} };
class WOMAN : public Base { void B() {} };

int main()
{
	Base* base_m = new MAN();
	Base* base_w = new WOMAN();
	return 0;
}

//이건 가상함수가 없는경우이다.

/*
아까의 예제에 Base에는 C()를 MAN과 WOMAN 클래스에 각각 무의미한 A(), B() 함수를 추가했다. 
결과는 예상한 대로 가상함수 테이블이 없어 RTTI 정보가 없기때문에 포인터의 타입을 가져온다.

타입id를 출력해보면,  (*base_w).name()  ==> class base가 출력될것이다.

virtual로 선언되지 않아서 단형성인 클래스가 되었고, 
이는 곧 가상함수 테이블이 없으면 RTTI 정보를 갖지 못하는 한계에 부딪힌다.
*/



#include <iostream>

class Base
{
	void C() {}
	virtual void GO() {}
};
class MAN : public Base
{
	void A() {}
	virtual void GO() {}
};
class WOMAN : public Base
{
	void B() {}
	virtual void GO() {}
};

int main()
{
	Base* base_m = new MAN();
	Base* base_w = new WOMAN();
	std::cout << typeid(*base_w).name() << std::endl;
	std::cout << typeid(*base_m).name() << std::endl;

	return 0;
}
//하지만 이것은 다를것.

/*
가상함수가 생기면서 가상함수 테이블이 생성되어 RTTI 정보가 제공되었다.
class MAN과 WOMAN이 출력될것이다.
*/







//MAP과 HashMap의 차이점.

/*
       "알고리즘 차이이다"

특정 키에 대한 값을 찾는 과정에서 MAP은 red black tree 알고리즘을 사용하고,
hashmap은 그 이름에서 알 수 있듯이 HASH 를 사용
(해시테이블을 이용해서 키-값 관계를 유지한다.)

map은 인터페이스이고, hashmap은 그 인터페이스의 구현이다.

  HashMap -------------- Map -------------------------- SortedMap
     |                   |                                   |
  LinkedHashMap       HashTable, WeakHashMap            TreeMap

*/






