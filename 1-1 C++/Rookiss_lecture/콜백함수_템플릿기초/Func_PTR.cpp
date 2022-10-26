#include<iostream>
using namespace std;


int Add(int a, int b) 
{
	return a + b;
}

int Sub(int a, int b)
{
	return a - b;
}

class Knight {
public:
	//멤버함수
	int GetHp(int, int)
	{
		cout << "GetHp()" << endl;
		return _hp;
	};
public:
	int _hp;
};

typedef int INTEGER;
typedef int* POINTER;
typedef int ARRAY[20];
typedef int(*PFUNC)(int, int); //함수 포인터
typedef int(Knight::* PMEMFUNC)(int, int); //멤버 함수 포인터



class Item 
{
public:
	Item() : _itemId(0), _rarity(0), _ownerId(0)
	{

	}

public:
	int _itemId; // 아이템을 구분하기 위한 ID
	int _rarity; // 희귀도
	int _ownerId; // 소지자 ID
};

Item* FindItemByItemId(Item items[], int itemCount, int itemId)
{
	//안전 체크

	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		//TODO 조건 
		if (item->_itemId == itemId)
			return item;
	}
	return nullptr;
}

//이렇게 여러개 해서 매개변수에 _itemId, _rarity, _ownerId 등등을 만들어 주며,
//Item* FindItemByRarity(Item items[], int itemCount, int rarity) 와 같은 여러 버전을 만들어야함
//이러면 유지보수가 어렵기 때문에 이를 방지하기 위해 다음과 같은 처리를 해준다.

typedef bool(ITEM_SELECTOR)(Item* item, int);

//일련의 처리를 해주기 위한 함수를 인자로 받는다. -> Main에서 쓰임새 확인하기
Item* FindItem(Item items[], int itemCount, /*함수*/ ITEM_SELECTOR* itemSelector, int value)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		if (itemSelector(item, value))
			return item;
	}
	return nullptr;
}

bool IsRareItem(Item* item, int )
{
	return item->_rarity >= 2;
}

bool IsOwnerItem(Item* item, int ownerId)
{
	return item->_ownerId == ownerId;
}

int main()
{
	int a = 10;
	//int* Pointer = &a;

	typedef int DATA;
	DATA* Pointer = &a;

	//함수
	/*int Add(int a, int b);*/
	typedef int(FUNC_TYPE)(int , int );
	using FUNC_TYPE2 = int(int a, int b); //위와 동일한 함수임.

	//1) 포인터
	//2) 변수 이름
	//3) 데이터 타입
	FUNC_TYPE* fn;
	fn = Add; // 만약 SUB를 만든다면, 이 함수 포인터만 바꾸어 SUB로 대채

	//함수의 이름은 함수의 시작 주소 (배열과 유사)
	int result = Add(1, 2);
	cout << result << endl;

	int result2 = fn(5, 5);
	cout << result2 << endl;

	int result3 = (*fn)(5, 5);
	cout << result3 << endl;

	Item items[10] = {};
	items[3]._rarity = 2;
	FindItem(items, 10, IsOwnerItem, 100);

	Knight k1;
	k1.GetHp(1, 1);

	PMEMFUNC mfn;
	mfn = &Knight::GetHp;
	(k1.*mfn)(1, 1);

	Knight* k2 = new Knight();
	
	(*k2.*mfn)(1, 1);

	delete k2;

	return 0;
}


//int main()
//{
//	//요약
//	int (*fn)(int, int);
//	fn = Add;
//	fn(1, 2);
//}