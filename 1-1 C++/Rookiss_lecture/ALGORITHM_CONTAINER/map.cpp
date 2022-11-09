//#include<iostream>
//#include<vector>
//#include<list>
//#include<deque>
//#include <map>
//#include <set>
//using namespace std;
////map
//
//class Player
//{
//public:
//	Player() : _playerId(0) {}
//	Player(int playerId) : _playerId(playerId) {}
//
//
//public:
//	int _playerId;
//
//};
//
//template<typename T1, typename T2>
//struct Pair
//{
//	T1 t1;
//	T2 t2;
//};
//
//int main()
//{
//	vector<Player*> v; //기존에 쓰던 벡터와 리스트와 같은 컨테이너의 문제점.
//					   //=> 10만명이 입장했다고 가정하자.
//
//	for (int i = 0; i < 100000; i++)
//	{
//		Player* p = new Player(i);
//		v.push_back(p);  //모두 동적할당으로 생성해서 벡터 컨테이너에 넣었다고 가정하자
//	}
//
//	//5만명이 퇴장했다고 가정하자
//	for (int i = 0; i < 50000; i++)
//	{
//		int randIndex = rand() % v.size();
//		Player* p = v[randIndex];
//		delete p;
//
//		v.erase(v.begin() + randIndex);
//	}
//	//5만명이 드문드문 들어가 있을거다.
//
//	//ID = 2만 플레이어가 ID = 1만 플레이어를 공격하고 싶다.
//	//Q)이때 ID=1만인 player를 찾아주세요. 
//	//A) 기존 벡터로 찾아보면 일일히 루프를 돌면서 찾아야한다.  ==> searching에 심한 문제가 있다.
//
//	//연관 컨테이너   --> 밀어넣은 순서에 따라 이뤄지는게 아니라, 실제 가지고 있는 데이터  따라.
//
//	// map : 균형 이진 트리 (AVL)
//	// - 노드 기반
//
//	class Node {
//	public:
//		Node* _left;
//		Node* _right;
//
//		pair<int, Player*> _data; //아래의 데이터들을 한번에 이렇게 저장하고 있다.
//		/*int _key;
//		Player* _value;*/
//
//
//
//	};
//	 //[key, map]
//	map<int, int>m;
//
//	//판별하는 식은
//	pair<map<int, int>::iterator, bool> ok;
//
//	ok = m.insert(make_pair(1, 100));
//	ok = m.insert(make_pair(1, 100)); //이렇게 두번 넣어도 소용이 없고, 값을 바꿔도 값은 바뀌지 않는다.
//	//값을 덮어쓴다면, 그냥 무시된다.
//
//
//	//10만명을 입장시키고 
//	for (int i = 0; i < 100000; i++)
//	{
//		m.insert(pair<int,int>(i, i*100));
//	}
//
//	//5만명을 퇴장시켜보자
//	for (int i = 0; i < 50000; i++)
//	{
//		int randomValue = rand() % 50000;
//
//		//key값을 이용해서 삭제해봤다
//		m.erase(randomValue);
//
//	}
//
//	// A) 매우 빠르게 찾을 수 있음.
//	map<int, int>::iterator findIt =  m.find(10000); //key값이 1만인 애를 찾아보쟈~~~~
//	if (findIt != m.end())
//		cout << "찾음" << endl;
//	else
//		cout << "못찾음" << endl;
//
//
//	//map 순회
//	//데이터가 따닥따닥 붙어 있는게 아니다.
//	//for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
//	//{
//	//	//(*it) 이 형식으로 보통 쓰는데, 이건 pair<const int, int>& p = (*it) 같은 형태이다.
//	//	int key = (*it).first;     //it->first
//	//	int value = (*it).second;  // p.second라고 써도 된다.
//
//	//	cout << key << " " << value << endl;
//	//}
//
//
//	//만약 없으면 추가하고 있으면 수정한다고 했을때,
//	//map<int, int> ::iterator it = m.find(300);
//	//if (it != m.end()) {
//	//	(*it).second = 400;
//	//}
//
//	//else
//	//	m.insert(300, 23041);
//
//	//만약 없으면 추가하고 있으면 수정한다고 했을때 2번째 방법
//	//m[5] = 500; //5라는 키값이 없으면, 500을 넣어준다.
//
//
//	//추가는 insert(key, value)
//	//삭제는 erase(key)
//	//찾기는 find(key);
//	//반복은 map::iterator(*it)pair<key, value>
//
//
//
//
//
//	//**********************************************************
//	//set, multimap, multiset
//
//	//key = value인 경우가 set이다.
//	//set (키만 단독적으로 활용) -> 키 자체가 데이터인 경우
//	set<int> s;
//	//넣기
//	s.insert(10); //바로 데이터 넣기 가능
//	s.insert(40);
//	s.insert(30);
//	s.insert(100);
//	s.insert(90);
//	s.insert(80);
//	s.insert(70);
//
//	//지우기
//	s.erase(30);
//
//	//찾기
//	set<int>::iterator newit = s.find(100);
//	if (newit == s.end())
//		cout << "없다.";
//
//	for (set<int>::iterator i = s.begin(); i != s.end(); ++i)
//	{
//		cout << (*i) << endl;
//	}
//
//
//
//
//
//	//multimap, multiset  ==> map에서 중복 키를 허용하는게 multimap   || set에서 중복 키를 허용하는게 multiset
//	multimap<int, int> mm;
//	mm.insert(make_pair(1, 100));
//	mm.insert(make_pair(1, 200));
//	mm.insert(make_pair(1, 300));
//	mm.insert(make_pair(2, 400));
//	mm.insert(make_pair(3, 500));
//
//	mm.erase(1);  //과연 이렇게 하면, 하나만 지워질까, 다 지워질까
//	//다 지워진다.
//
//	multimap<int, int>::iterator itFind = mm.find(1);
//	if (itFind != mm.end())
//		mm.erase(itFind);
//	
//	mm.equal_range(1); // iterator를 쌍으로 묶어서 건내주고 있다.
//
//
//	return 0;
//}