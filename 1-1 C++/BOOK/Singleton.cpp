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

