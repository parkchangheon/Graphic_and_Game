

#include <iostream>

using namespace std;

class Foo
{
public:
	void PrintFooVal() { cout << "fooval : " << fooval << endl; }
private:
	int fooval = 34;
};

class Document
{
public:
	int AskUserDocumentNum() { return DocumentNum; }
private:
	int DocumentNum = 10;
};

int main()
{


}

void NewDelete()
{
	//이러한 지역변수들은 스택에 저장이된다.
// 이러한 변수들은 일정한 스코프 (유효범위)를 넘어가게 되면 할당된 메모리가 자동으로 삭제된다.
	int i = 7;


	// new를 사용한 동적 메모리 할당은 프리스토어에 저장되게 된다.
	// ptr 자체는 스택 메모리에 있지만, 프리스토어의 메모리를 가리키고 있는 것이다.

	// 스택            프리스토어
	// ptr   ------->  *ptr
	int* ptr = new int;

	// 포인터는 스택에도, 프리스토어에도 모두 있을 수 있다.
	// 스택             프리스토어
	// handle   ----->  *handle
	//                    |
	//                    v
	//                  **handle

	int** handle = nullptr;
	handle = new int*;
	*handle = new int;


	//new - delete
	// 변수에 필요한 메모리 블록을 할당 하기 위해 new를 사용한다. 
	// new의 리턴값을 무시하거나 포인터를 담은 변수가 스코프를 벗어나게 되면, 미아(orphan) 즉 메모리 누수(leak)가 발생함.
	// NewDeleteLeakFunc() 참고

	//올바른 해제 방식
	int* ptr = new int;
	delete ptr;
	ptr = nullptr;  // 메모리를 해제했다면 nullptr로 초기화하는 것이 중요한데, 이미 해제된 메모리를 다시 쓰는 불상사를 막기 위함
}

void NewDeleteLeakFunc()
{
	// 할당하고 해제해주는 곳이 없음.
	// 더욱이 데이터 블록에 접근할 수 가 없음.
    new int;    //벌써 메모리 릭.
}

void NewDeleteFailed()
{
	// new가 실패하는 경우는 보통, 메모리가 부족해서 발생하는 경우가 일반적.
	// new가 실패하면 익셉션을 던지는데, 요청한 만큼 메모리가 없을때 던짐.

}


void Mem_Malloc()
{
	// Malloc은 인수로 지정한 바이트 수 만큼 메모리를 할당해준다.
	// 하지만 malloc 보다는 new를 쓰는게 바람직함. ==> 객체까지 만들어주기 떄문.

	Foo* newFoo = new Foo;
	Foo* mallocFoo = { (Foo*)malloc(sizeof(Foo)) };

	//mallocFoo 객체가 가리키는 Foo는 아직 생성된 것이 아니기에, 정식 객체는 아니다. (메모리 영역만을 뺴놓을 뿐이다.)
	//newFoo 의 경우엔 적절한 크기의 메모리 할당 + Foo 생성자를 호출해서 객체를 생성한것.

	// free의 경우도 마찬가지이다.
	// free의 경우엔 소멸자를 호출하지 않는 반면, delete는 소멸자를 호출하여 객체를 정상적으로 소멸시킴.
}


void MemoryArray()
{
	int array1[5]{ 1,2,3,4,5 };
	int array2[5]{ 1,2 };	// 1,2,0,0,0
	int array3[5]{};		// 0,0,0,0,0

	// 스택           프리스토어
	// myarray[0]
	// myarray[1]
	// myarray[2]
	// myarray[3]
	// myarray[4]



	int* myArrayptr = new int[5];
	// 스택					프리스토어
	// myArrayptr	-->		myArrayptr[0]
	//						myArrayptr[1]
	//						myArrayptr[2]
	//						myArrayptr[3]
	//						myArrayptr[4]

	// 저 위의 new에서 인수로 (nothrow)를 지정하면 메모리 할당 실패시 익셉션을 던지지 않고 nullptr를 던짐.
	int* myArrayptr2 = new(nothrow) int[5];

	int* myArrayptr3 = new int[] {1, 2, 3, 4, 5};
	delete[] myArrayptr;
	delete[] myArrayptr2;
	delete[] myArrayptr3;

	myArrayptr = nullptr;
	myArrayptr2 = nullptr;
	myArrayptr3 = nullptr;
}

Document* createDocArray()
{
	size_t numDocs;
}