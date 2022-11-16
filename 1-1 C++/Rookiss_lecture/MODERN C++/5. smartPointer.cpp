#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include <vector>

using namespace std;

//smart pointer 
//개요
//포인터는 직접적으로 메모리를 읽고 수정이 가능한데, 엉뚱한 메모리를 읽으면 큰일난다.


class Knight
{
public:
	~Knight() { cout << "나이트 소멸" << endl; }
	Knight() { cout << "나이트 생성" << endl; }


	void Attack()
	{
		if (_target)  //타겟이 없으니 이상한 메모리를 건들고 있다.
		{
			_target->_hp -= _damage;
			cout << "HP : " << _target->_hp << endl;
		}
	}


public:
	int _hp = 100;
	int _damage = 100;
	Knight* _target = nullptr;

};


class RefCountBlock  //참조횟수를 관리하는 클래스
{
public:
	int _refCount = 1;
};

template<typename T>
class SharedPtr 
{
	//포인터를 참조하는 애들을 카운트해서 0이 아니면 delete 처리 x
public:
	SharedPtr() {}
	SharedPtr(T* ptr) : _ptr(ptr)
	{
		if (_ptr != nullptr) 
		{
			block = new RefCountBlock();
			cout << "RefCount" << block->_refCount <<endl;
		}
	}

	~SharedPtr() 
	{
		if (_ptr != nullptr)
		{
			_block->_refCount--;
			cout << "RefCount" << block->_refCount << endl;

			if (_block->_refCount == 0)
			{
				delete _ptr;
				delete _block;
				cout << "Delete Data" << endl;
			}
		}
	}


public:
	T* _ptr = nullptr;
	RefCountBlock* _block = nullptr;
};

int main()
{
	Knight* k1 = new Knight();
	Knight* k2 = new Knight();

	k1->_target = k2;  //타겟 설정을 해줬는데
	delete k2;		   //삭제를 해줬다?!?!!
	k1->Attack();	   //문제 발생. 

	//스마트 포인터 : 포인터를 알맞는 정책에 따라 관리하는 객체( 포인터를 래핑해서 사용 )
	//shared_ptr, weak_ptr, unique_ptr


	//shared ptr(핵심)



	return 0;
}