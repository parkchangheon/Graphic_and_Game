//잘못된 구현의 예 of Singleton

//#include<iostream>
//using namespace std;
//class Singleton {
//private:
//	static Singleton s; 
//
//public:
//	static Singleton& getInstace() {
//		return s;
//	}
//};
//
//
//Singleton Singleton::s;  //전역변수로써 초기화
//
//int main() {
//	Singleton& s = Singleton::getInstace();
//	return 0;
//}

//생성자, 복사생성자, 소멸자를 private 처리를 해주지 x 
//==> 이런 경우에 static 객체는 복사가 되어 사용하는 의미를 잃어버린다.
// 
// 늦은 초기화 
//프로그램이 시작과 동시에 초기화 되는 것을 방지하여, 사용자가 원하는 시점에 객체의 초기화를 해주는 것!!
//ex)
//static int num1 = 0;
//static int num2 = 0;
//static int num3 = 0;
//static int num4 = 0;
//static 같은 경우는 전역변수에 마구잡이로 선언이 되어도 초기화 되는 순서는 랜덤이다.
// 변수들이 순서대로 초기화 되어도 실제로는 어떤게 먼저 될지 모름!


#include<iostream>
using namespace std;
class Singleton {
private:
	static Singleton s;

public:
	static Singleton& getInstace() {
		return s;
	}
};

class A {
public:
	A() {
		Singleton& s = Singleton::getInstace();
	}
};


Singleton Singleton::s;  //전역변수로써 초기화

int main() {
	Singleton& s = Singleton::getInstace();
	return 0;
}



////////////////////////////////////////////////////////////////


//복사생성자
//얕은 복사 => 동적 할당 받은 변수의 주소값을 공유한다.
//깊은 복사 => 새로이 동적할당은 받고, 원본의 데이터 까지 복사.

//객체의 복사가 이루어질때 호출되는 생성자.


//예시

//#include<string>
//using namespace std;
//
//class ChangHeon {
//
//	int age;
//	string name;
//protected:
//	string DNA;
//
//public:
//	ChangHeon(); //생성자이고
//	ChangHeon(int age, string name, string DNA);
//	~ChangHeon();
//
//	ChangHeon(ChangHeon& dRef);   //여기가 복사생성자이다.
//
//	//setter method
//	void setAge(int age) { this->age = age; }
//	void setName(string name) { this->name = name; }
//	void setDNA(string DNA) { this->DNA = DNA; }
//
//	//getter method
//	int getAge() { return age; }
//	string getName() { return name; }
//	string getDNA() { return DNA; }
//
//	ChangHeon* getSelf() { return this; }
//
//	void showInfo();
//	void grow(int age);
//	void shit(string food);
//};
//
//
//ChangHeon::ChangHeon(ChangHeon& dRef) {
//	name = dRef.getName();
//	age = dRef.getAge();
//	DNA = dRef.getDNA();
//
//	cout << name << "이가 복사되었다." << endl;
//}




//싱글톤 패턴 -> 하나의 인스턴스만 생성하여 사용하는 디자인 패턴

//생성자가 여러번 호출되도 실제로 생성되는 객체는 하나이다.
//최초로 생성된 이후에 호출된 생성자는 이미 생성한 객체를 반환한다.


//메모리 낭비 방지 가능. => 한번의 new를 통해 객체를 생성한다면 메모리 방지
//싱글톤 구현한 인스턴스는 '전역'  => 다른 클래스의 인스턴스들이 데이터를 공유가능

//많이 사용하는 경우는, 공통된 객체를 여러개 생성해서 사용하는 상황에 사용됨
//DB에서 커넥션풀, 스레드풀, 캐시, 로그 기록 객체 등.
//AOS : 각 액티비티들이나, 클래스마다 주요 클래스들을 하나하나 전달하는게 번거롭기 때문에 싱글톤 클래스를 만들어 어디서든 접근하도록 설계
//혹은 인스턴스가 절대적인 하나다 라는것을 보증하고 싶을 때 사용.


//개방 폐쇄 원칙 : 여기저기에서 싱글톤 인스턴스 혼자 너무 많은 일을 하거나, 많은 데이터를 공유하면 다른 클래스간 결합도가 높아져, 개방 폐쇄 원칙에 위배됨.
//멀티 스레드 환경에서 동기화 처리 부재시, 인스턴스가 2개가 생성되는 문제가 발생할 수 있다.



//멀티 스레드 환경에서 안전한 싱글톤 만드는법!
