#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

//포인터는 직접적으로 어떤 메모리를 읽고 쓰는 장점이 있는데, 이게 위험하기도 하다..
//=>

class Knight
{
public:
	Knight() { cout << "Knight 생성되었다. " << endl; }
	~Knight() { cout << "Knight 소멸되었다. " << endl; }



	void Attack() 
	{
		if (_target.expired() == false)
		{
			shared_ptr<Knight> sptr = _target.lock();
			sptr->_hp -= _damage;
			cout << "target hp : " << sptr->_hp << endl;
		}
	}



public:
	int _hp = 100;
	int _damage = 10;
	//Knight* _target = nullptr;   //생포인터를 써서!! 그래서 바꿔보자
	weak_ptr<Knight> _target;      //객체가 날아갔는지 안날아 갔는지 확인하는 용도로 사용이 가능하다.
	//장점 : Knight 객체의 소멸과 연관이 없지만, 위의 Attack 처럼 expired과 같이 명시적으로 체크 + shared_ptr로 변환
	//메모리 구조에서 자유로울 것이냐 <-> 사용이 편할것이냐
};



//Shared_Ptr

//RefCounter
class RefCountBlock  //참조 횟수를 감시
{
public:
	int _refCount = 1;  //진짜 몇개가 얘를 참조하고 있느지.
	int _weakCount = 1; //이러한 weakPointer 몇개가 RefCountBlock을 참조하고 있는지. 
};

template<typename T>
class SharedPtr //참조 카운트를 한다. (몇명이나 이 포인터를 참조하고 있냐 ? 이 객체를 아무도 기억하고 있지 않을때 delete)
{
public:
	SharedPtr() { }
	SharedPtr(T* ptr) : _ptr(ptr) {
		if (_ptr != nullptr)
		{
			_block = new RefCountBlock;
			cout << "RefCount : " << _block->_refCount << endl;
		}
	}
	SharedPtr(const SharedPtr& sptr) : _ptr(sptr._ptr), _block(sptr._block)
	{
		if (_ptr != nullptr)
		{
			_block->_refCount ++; // 상대방이 들고 있는 카운터 ++해줌
			cout << "RefCount : " << _block->_refCount << endl;

		}
	}

	void operator=(const SharedPtr& sptr)
	{
		_ptr = sptr._ptr;
		_block = sptr._block;
		if (_ptr != nullptr)
		{
			_block->_refCount++;
			cout << "RefCount : " << _block->_refCount << endl;

		}
	}

	~SharedPtr() {
		if (_ptr != nullptr)
		{
			_block->_refCount--;
			cout << "RefCount : " << _block->_refCount << endl;
			if (_block->_refCount == 0)
			{
				delete _ptr;
				delete _block;  //weak_ptr을 사용하면 기존에 pointer의 refCounter가 0이 되었으면
				cout << "Delete Data" << endl;

			}
		}
	}
public:
	T* _ptr = nullptr; //원본 객체 포인터
	RefCountBloack* _block = nullptr;
};

int main()
{
	/*
	Knight* k1 = new Knight();
	Knight* k2 = new Knight();
	k1->_target = k2;
	k1->Attack();

	//이때 k2의 유저가 나갔다. ==>소멸시켜야하는데
	delete k2; //이렇게 하면, 기존에 위에 Attack에서 _target 처리해준 애는 어떻게될까? (크래시는 안나되, 메모리는 날아가버린 상태가 되었다.)
	//그래서 위의 Attack에서는 엉뚱한 메모리를 만지는 결과를 초래하는데, 이러한 이유는 그냥 생pointer를 사용했기 때문이다.
	*/

	//스마트 포인터는 
	//*** shared_ptr ***, weak_ptr, unique_ptr 이 있다.


	//SharedPtr<Knight> k2;
	////사용법 
	//{
	//	SharedPtr<Knight> k1(new Knight());
	//	k2 = k1;
	//}

	shared_ptr<Knight> k1 = make_shared<Knight>();  //new Knight해도 되는데 make_shared가 성능이 더 좋다.
	shared_ptr<Knight> k2 = make_shared<Knight>();
	//k1->_target = k2;
	

	k1->Attack();
	
	// 그런데 이런 shared_ptr도 단점이 있다..! (사이클 관리가 안된다는건데, 아래 케이스이다.)
	k1->_target = k2;
	k2->_target = k1;
	//이때 서로가 서로를 주시하니, refcount가 일단 위에서 make_shared할떄 카운트가 1로 셋이 될테고, 서로가 서로를 타게팅할테니 2로 증가한다. 그리고 만약, k2가 어떤 이유로 delete가 되었을 때
	// refcount가 1 줄어들면,
	//k1 [  2]
	//k2 [  1]
	
	//과 같이 될것이다. 그리고 끝.... => 그럼 더이상 떨어질게 없다.
	//메모리가 절대 소멸이 안된다. (순환 문제...!!!)

	//해결하기 위해서는 아래처럼 nullptr로 밀어버리는 방법도 있다.
	//k1->_target = nullptr;
	//k2->_target = nullptr; 

	//하지만 이것을 해결하기 위해 weak_ptr을 사용한다.
	//순환 구조가 일어날 수 있는 부분을 weak_ptr로 바꿔준다. 그리고 refcount에 weakcount를 추가해준다.



	//unique_ptr (나만 이포인터를 가리켜야한다!!) (넘겨주기 안되어서, std:move로만 이동이 가능하다)
	unique_ptr<Knight> uptr = make_unique<Knight>();
	//unique_ptr<Knight> uptr2 = uptr; 에러


	return 0;

}