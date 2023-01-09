#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

enum class ItemType
{
	None,
	Armor,
	Weapon,
	Jewelry,
	Consumable,
};

enum class Rarity
{
	Common,
	Rare,
	Unique,
};


class Item
{
public:
	Item() {}
	Item(int itemId, Rarity rarity, ItemType type) : _itemId(itemId), _rarity(rarity), _type(type){}

public:
	int _itemId = 0;
	Rarity _rarity = Rarity::Common;
	ItemType _type = ItemType::None;
};

int main()
{
	vector<Item> v;
	v.push_back(Item(1, Rarity::Common, ItemType::Weapon));  //오른값으로 받아주고 있다
	v.push_back(Item(2, Rarity::Common, ItemType::Armor));
	v.push_back(Item(3, Rarity::Rare, ItemType::Jewelry));
	v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));




	//람다는 함수 객체를 손쉽게 만드는 방법이다.
	{
		struct IsUniqueItem    //함수객체가 함수 포인터보다 장점은 데이터를 저장할 수 있다.
		{
			bool operator()(Item& item)
			{
				return item._rarity == Rarity::Unique;
			}
		};

		struct FindItemByItemId
		{
			FindItemByItemId(int itemId, Rarity rarity, ItemType type) : _itemId(itemId), _rarity(rarity), _type(type)
			{

			}

			bool operator()(Item& item)
			{
				return item._itemId == _itemId;
			}


			int _itemId;
			Rarity _rarity;
			ItemType _type;
		};
	}



	int itemId = 4;
	//클로저(closure) : 람다에 의해 만들어진 실행시점 객체
	auto isUniqueLambda = [](Item& item) {return item._rarity == Rarity::Unique; }; //람다표현식
	//기본 캡쳐 모드 : 참조방식(&) vs 복사방식(=)
	auto FindItemByItemId = [=](Item& item) {return item._itemId == itemId; };   //[] capture : 함수 객체 내부에 변수를 저장하는 개념과 유사. (함수 외부에 있는 애를 갔다가 쓸 수 있다.)
	auto FindItemByItemId2 = [&](Item& item) {return item._itemId == itemId; };   //위 구조체에서 int -> int&와 같다고 생각해라 즉 item의 주소값으로 활용하고 있다.
	
	//그리고 위처럼 &, = 로 써주는 것 도 좋지만, 어떤것이 실제 사용되었는지 알기 쉽게 아래와 같이 써주는것도 괜찮은 방법이다.
	auto FindItemByItemId2 = [&itemId](Item& item) {return item._itemId == itemId; };   



	auto findit = std::find_if(v.begin(), v.end(), FindItemByItemId);
	if (findit != v.end())
	{
		cout << "아이템 ID : " << findit->_itemId << endl;
	}

	



	return 0;
}