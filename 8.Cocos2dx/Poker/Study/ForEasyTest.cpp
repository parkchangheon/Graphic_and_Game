//#include<iostream>
//#include<functional>
//using namespace std;
//
//
//class TEST {
//public:
//	typedef std::function<void* ()> TestFunction;
//	// stD::function이 처리할 수 있는 callable target은 다음과 같다.
//	// 일반함수, lambda 식, bind expression, 함수 객체, class 내의 멤버 함수 및 멤버 변수
//
//	//사용 방식이 
//	//std::function<리턴타입(입력 파라미터들)> 변수
//
//	//void print(int a, int b);
//	//std::function<void(int, int)> fp = print;
//};
//
//int main()
//{
//	
//}



//std::bind
//std:bind(함수의 주소, 인자1, 인자2, ...);
//간단하게 말하면 호출이 가능한 객체에 인수를 바인딩하는것.

//#include<iostream>
//#include<string.h>
//#include<functional>
//
////예제
//
//void hello(const string& s)
//{
//	cout << s << endl;
//}
//
//int main()
//{
//	auto func = std::bind(hello, "hello world"); // 바인드 과정
//	func(); //호출
//}

//#include<iostream>
//#include<functional>
//
//using std::placeholders::_1;   
// 인자값을 새로운 함수의 인자로 받을 수 있도록한다.


//#include<iostream>
//#include<functional>
//
//int sum(int a, int b, int c)
//{
//	return a + b + c;
//}
//
//int main()
//{
//	/*auto func1 = std::bind(sum, std::placeholders::_1,2, 3);
//	std::cout << func1(1) << std::endl;*/
//	// placeholder의 첫번째 인수만 입력을 받은것이고, 2번째 3번째 인수는 2와 3으로 고정
//	// 저 밑에 짝대기가 변경 가능하다는 뜻
//	//ex2)
//	/*auto func2 = std::bind(sum, std::placeholders::_1, std::placeholders::_2, 3);
//	std::cout << func2(1,4) << std::endl;*/
//}





//functional

//#include<iostream>
//#include<functional>
//
//using std::placeholders::_1;
//
//void print_number(int i)
//{
//	std::cout << i << std::endl;
//}
//
//void print_sum(int a, int b)
//{
//	std::cout << a + b << std::endl;
//}
//
//
//struct PrintNum
//{
//	void operator()(int i)const
//	{
//		std::cout << i << std::endl;
//	}
//};
//
//
//struct Foo
//{
//	int num_;
//	Foo(int num) : num_(num){}
//	void print_add(int i) const { std::cout << num_ + i << '\n'; }
//};
//
//int main()
//{
//	//일반 함수 방식
//	std::function<void(int)> f1 = print_number;
//	f1(10);
//
//	//람다식
//	std::function<void(int)> f2 = [](int a) {print_number(a); };
//	f2(10);
//
//}



// 싱글톤 패턴

//어플리케이션이 시작될때 어떤 클래스가 최초한번만 메모리를 할당하고
//그 메모리에 인스턴스를 만들어 사용하는 디자인 패턴이다.

//ex) 레지스트리 같은 설정 파일의 경우 객체가 여러개 생성되면 설정 값이 변경될 위험이 생길 수 있음
//인스턴스가 1개만 생성되는 특징을 가진 싱글턴 패턴을 이용하면, 하나의 인스턴스를 메모리에 등록해서 여러 쓰레드가 동시에 해당
//인스턴스를 공유하여 사용할 수 있게끔 할 수 있어 요청이 많은 곳에서 사용하면 효율을 높일 수 있다.
//동시성 문제를 고려해서 설계해야함


//싱글톤 패턴의 장점
//고정된 메모리 영역을 얻으면서 한번의 new로 인스턴스를 사용하기 때문에 메모리 낭비를 방지할 수 있다.
//싱글톤으로 만들어진 클래스의 인스턴스는 전역이기 때문에 다른 클래스의 인스턴스들이 데이터공유가 원활
//인스턴스가 절대적으로 한개만 존재하는 것을 보증하고 싶을 경우 사용한다.
//두번째 이용시 부터는 객체 로딩 시간이 줄어 성능이 좋아지는 장점이 있다.


//단점은
//싱글톤 인스턴스가 너무 많은 일을 하거나 많은 데이터를 공유시킬 경우에, 다른 클래스의 인스턴스들 간에 결합도가 높아져 
//"개방 폐쇄 원칙"을 위배하게 된다.

//이는 객체 지향 설계 원칙에 어긋나기 때문에 수정이 어려워지고 유지보수의 비용이 높아질 수 있다.
//또한 멀티쓰레드 환경에서 동기화 처리를 안하면 인스턴스가 2개 생성될 수 있는 가능ㅅㅇ이 생길 수 있다.


//ex)

//싱글톤 패턴 예제

#include <cstddef>
class FileSystem {

public:
	static FileSystem& instance() {  // 정적 메서드는 코드 어디에서나 싱글턴 인스턴스에 접근할 수 있게 함.
	// 정적메서드는 클래스의 인스턴스 없이 호출이 가능하며, 인스턴스에서는 호출이 불가능.
	// 유틸리티 함수를 만드는데 유용하게 사용된다.
	// 싱글턴을 실제로 필요로 할 때까지 인스턴스 초기화를 미루는 역할도 한다.
		
		//게으른 초기화
		if (instance_ == NULL) {
			instance_ =  new FileSystem();
		}
		return *instance_;
	}

private:
	FileSystem(){}
	static FileSystem* instance_; // 정적 멤버 변수는 클래스 인스턴스를 저장한다. private이기에 밖에서 생성 불가.
};