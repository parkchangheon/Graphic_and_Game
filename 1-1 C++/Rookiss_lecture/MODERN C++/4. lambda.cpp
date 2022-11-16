#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include <vector>

using namespace std;

enum class ItemType
{
	None,
	Armor,
	Weapon,
	Jewelry,
	Consumable
};

enum class Rarity
{
	Common,
	Rare, 
	Unique
};

class Item
{
public:
	Item();
	Item(int itemId, Rarity rarity, ItemType type)
		: _itemId(itemId), _rarity(rarity), _type(type)
	{

	}

public:
	int _itemId = 0;
	Rarity _rarity = Rarity::Common;
	ItemType _type = ItemType::None;
};



//int main()
//{
//	vector<Item> v;
//	v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
//	v.push_back(Item(2, Rarity::Common, ItemType::Armor));
//	v.push_back(Item(3, Rarity::Rare, ItemType::Jewelry));
//	v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));
//
//
//
//	
//	{
//		struct IsUniqueItem //해당 구조체는 지속적으로 쓰지 않음.
//		{
//			bool operator()(Item& item)
//			{
//				return item._rarity == Rarity::Unique;
//			}
//		};
//
//		auto findIt = std::find_if(v.begin(), v.end(), IsUniqueItem()); //해당 find에서 조건이 걸린 함수는 한번만 쓰고 안씀
//		if (findIt != v.end())
//			cout << "아이템 ID : " << findIt->_itemId << endl;
//	}
//
//
//
//	{
//		int itemId = 4;
//		Rarity rarity = Rarity::Unique;
//		ItemType type = ItemType::Weapon;
//
//		//람다(lambda)를 사용하면 위의 과정이 축약이 될 수 있다.!!!
//		//람다는 [](){}로 선언을 하는데 아래와 같다
//
//		//클로저(closure) = 람다에 의해 만들어진 실행시점 객체
//		auto IsUniquelambda = [](Item& item) {return item._rarity == Rarity::Unique; }; 
//
//		//[ ] 캡처(capture) : 함수 객체 내부에 변수를 저장하는 개념과 유사 
//		//기본 책처 모드 : 값(복사) 방식(=)  <=>  참조방식(&)
//		//전달하는 변수마다 캡처모드를 다르게 할 수 도 있다.
//		auto findByItemIdLambda = [=](Item& item) {return item._itemId == itemId; };  //외부의 값을 전달받아 itemId에 저장해줌.
//		auto findByItemIdLambda2 = [&](Item& item) {return item._itemId == itemId; };  //&로 바꾸면 =과 무슨 차이일까?
//		//&를 붙인다면, 받는 매개변수들이 모두, 참조 형태이다 (&가 붙어서)
//
//		auto findByItemIdLambda3 = [&itemId, rarity, type](Item& item) {return item._itemId == itemId && item._rarity == rarity && item._type == type; };
//		//위 방법처럼 받는 매개변수를 값/참조 방식 나눠서 받을 수도 있음.
//
//		itemId = 1;
//
//		auto findIt = std::find_if(v.begin(), v.end(), findByItemIdLambda2); //해당 find에서 조건이 걸린 함수는 한번만 쓰고 안씀
//		if (findIt != v.end())
//			cout << "아이템 ID : " << findIt->_itemId << endl;
//
//
//		auto findIt2 = std::find_if(v.begin(), v.end(), findByItemIdLambda3); //해당 find에서 조건이 걸린 함수는 한번만 쓰고 안씀
//		if (findIt2 != v.end())
//			cout << "아이템 ID : " << findIt2->_itemId << endl;
//
//
//
//
//		class Knight
//		{
//		public:
//			auto ResetHpJob() // 람다는 어떤 타입으로 return 할지 정확하지 않아 auto로 리턴값 처리를 해준다.
//			{
//				//auto f = []() {_hp = 200; }; // 오류가 나는 이유는 사실     auto f = [this]() {this->_hp = 200; }; 이런식이다. 이건 knight객체를 받아오기에 옳바르지 않은 방식이다. 
//				auto f = [this]() {this->_hp = 200; };
//
//				return f;
//			}
//
//		public:
//			int _hp = 100;
//
//		};
//
//		Knight* k = new Knight();
//		auto job = k->ResetHpJob();
//		delete k;
//		job(); 
//		//메모리 오염
//
//	}
//
//
//
//	return 0;
//}