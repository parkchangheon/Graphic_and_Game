/* 
아무 곳에서나 파일 시스템 클래스 인스턴스를 만들 수 있다면, 다른 인스턴스에서 어떤 작업을 진행중인지를 알 수 없다. 
싱글턴으로 만들게 된다면, 클래스가 인스턴스를 하나만 가지도록 컴파일 단계에서 강제할 수 있다.
*/



#include<iostream>
using namespace std;

// 전역 접근점을 제공 ==> 따로 인스턴스를 생성할 수 없으므로, 전역에서 접근할 수 있는 메서드를 제공한다.
class FileSystem
{
private:
	FileSystem() {}
	static FileSystem* instance_; //해당 정적 멤버 변수는 클래스 인스턴스를 저장한다. private이므로 외부에서는 생성이 불가.

public :
	static FileSystem instance(){			// 어디에서나 접근이 가능하고, 실제로 필요할 때까지 인스턴스 초기화를 미루는 역할도 함.
		//lazy initialize
		if (instance_ == NULL) {
			instance_ = new FileSystem();
			return *instance_;
		}
	}
};

//최근 제작 방식 
class FileSystem2 {
private:
	FileSystem2() {}

public:
	static FileSystem2 Instance() {
		static FileSystem2* Instance_ = new FileSystem2;
		return *Instance_;
	}
};

//한번도 사용하지 않았다면, 아예 인스턴스를 생성하지 않는다. => 메모리, CPU사용량을 줄일 수 있다.
//처음 사용될때, 초기화가 되므로 게임내에서 전혀 사용되지 않는다면, 초기화 되지도 않는다.

// 런타임에 초기화가 된다.
 
 




// 싱글턴을 상속할 수 있다.
class FileSystem3 {
public:
	static FileSystem3& instance();

	virtual ~FileSystem3() {};
	virtual char* readFile(char* path) = 0;
	virtual void writeFile(char* path, char* contents) = 0;

	//FileSystem 클래스를 싱글턴으로 만든다.
protected:
	FileSystem3() {}
};

FileSystem3& FileSystem3::instance() {	// 해당 함수를 통해 접근하기 때문에, 플랫폼 전용 코드는 FileSystem 내부에 숨겨 놓을 수 있다.
#if PLATFORM == PS4
	static FileSystem3* instance = new PS4FileSystem;
#elif PLATFORM == NINTENDO
	static FileSystem3* instance = new NintendoFileSystem;
#endif
	return *instance;

}



class PS4FileSystem : public FileSystem3 {
public:
	virtual char* readFile(char* path) {
		//ps4 파일 IO API를 사용한다.
	}
	virtual void writeFile(char* path, char* contents) {
		//ps4 파일 IO API를 사용한다.
	}
};

class NintendoFileSystem : public FileSystem3 {
public:
	virtual char* readFile(char* path) {
		//ps4 파일 IO API를 사용한다.
	}
	virtual void writeFile(char* path, char* contents) {
		//ps4 파일 IO API를 사용한다.
	}
};

// 전역변수와 싱글톤의 차이는 생성 시점을 
// lazy init을 통해 초기화를 늦출 수 있고, 구조에 유연하고 상속을 통해 멀티플랫폼에 대응이 가능하다

// 주로 로깅이나, DB, 프린터 스풀러 등 동일한 리소스에 대한 동시 요청의 충돌을 막기 위해 사용된다.
// 클래스에 대한 단일 객체 생성, 전역 객체 제공, 공유된 리소스에 대한 동시 접근 제어

//싱글톤의 문제점..

// 알고 보니 전역 변수 ==> 전체코드에서 Instance가 쓰인곳을 전부 찾아봐야한다.
// 전역 변수는 커플링을 조장하고, 멀티스레딩 같은 동시성 프로그래밍에 어울리지 않음.
// 예를 들어, 
// "물체가 떨어지면 사운드가 난다" 라는 작업이 주어졌을 경우,
// 오디오 플레이 인스턴스에 전역적으로 접근할 수 있다고 하면 include 한줄이면 아키텍쳐가 엄청 더러워 진다.

// 오디오 플레이 인스턴스를 만들지 않았더라면, include를 추가해도 어찌할 방법이 없었을 것이다.

//*****************인스턴스에 대한 접근을 컨트롤 하는 것이 커플링을 통제하는 것! ***************************************



// 게으른 초기화는 제어할 수 가 없었다.
// 가상메모리도 사용가능하며, 성능 요구도 심하지 않은 PC에서는 게으른 초기화가 좋은 기법이나, 게임은 다르다.
// (가상메모리는 어플리케이션을 실행하는데, 얼마나 많은 메모리가 필요한지가 아닌, 최소 얼마만큼이 필요한지에 집중)
// 메모리는 순차적으로 접근화가 되어있고, 지역화가 되어있기때문.
// 가상 메모리는 메모리가 실제 메모리보다 많아 보이게 하는 기술. 
// 어떤 프로세스가 실행될 때, 메모리에 해당 프로세스 전체가 올라가지 않더라도 실행이 가능한 점에서 착안됨.

