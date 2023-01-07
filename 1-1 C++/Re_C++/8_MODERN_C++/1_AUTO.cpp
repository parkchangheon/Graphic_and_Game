#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

class Knight
{
public:
	int _hp;
};

template<typename T>
void Print(T t)
{
	cout << "print call  "<< t <<endl;
}

int main()
{
	//int a = 3;
	//float b = 3.14f;
	//double c = 1.23;
	//Knight d = Knight();
	//const char* e = "string";

	auto a = 3;
	auto b = 3.14f;
	auto c = 1.23;
	auto d = Knight();
	auto  e = "string";

	auto f = &d;
	const float test1 = b;
	auto* test2 = e;  // const char*

	Print<int>(1);

	//=============//
	//기본 auto는 const, &무시
	int& ref = a;
	const int cst = a;

	auto test3 = ref;  // int ref = a;
	auto test4 = cst;  // int cst = a; 가 된다.


	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		//auto 를 사용하지 않고 데이터 값을 바꾸는것.
		int& data = v[i];   //int& != auto
		//auto& data = v[i]; 를 쓰던가
		//auto data = static_cast<int&>v[i];를 해주던가 한다.

		data = 100;
	}

	//사용 case 1 
	map<int, int> m;
	auto ok = m.insert(make_pair(1, 100));
	ok.first;
	ok.second;

	//사용 case2
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}

	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}

	return 0;
}