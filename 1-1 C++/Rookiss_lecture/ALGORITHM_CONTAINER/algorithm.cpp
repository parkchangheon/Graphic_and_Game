#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int number = 30;
	vector<int> v;
	v.push_back(11);
	v.push_back(31);
	v.push_back(20);
	v.push_back(40);
	v.push_back(70);
	v.push_back(90);
	v.push_back(100);

	/*vector<int>::iterator it = v.end();*/
	//기존에 벡터만을 사용해서 특정 데이터를 찾고자 했다면
	//for문을 돌아 일일히 검사를 해서 찾으면 break를 해줬다.
	
	//하지만 algorithm find를 활용한다면,
	vector<int>::iterator it = find(v.begin(), v.end(), number);
	//한줄로 정리가 가능하다.

	if (it == v.end())
		cout << "Cant find the thing!" << endl;

	struct CanDivide11 {
		bool operator()(int n)
		{
			return (n % 11) == 0;
		}
	};

	vector<int>::iterator itFind = find_if(v.begin(), v.end(), CanDivide11()); //나뉘는 첫번째 아이를 꺼내준다.
	if (itFind == v.end())
		cout << "Cant find the thing!" << endl;
	

	struct IsOdd {
		bool operator()(int n)
		{
			return (n % 2) != 0;
		}
	 };

	int n = count_if(v.begin(), v.end(), IsOdd());
	cout << n << endl;

	//모든 데이터가 조건을 만족하느냐
	bool b1 = all_of(v.begin(), v.end(),IsOdd()); //모두냐?
	bool b2 = any_of(v.begin(), v.end(), IsOdd());//하나냐?
	bool b3 = none_of(v.begin(), v.end(), IsOdd());// 없냐?

	// 모든 데이터가 만족하느냐!


	struct MultiplyBy3 {
		void operator()(int& n) {
			n *= 3;
		}
	};

	for_each(v.begin(), v.end(), MultiplyBy3()); //모든 데이터를 대상으로 *3을 해주었다.


	{ //홀수인 데이터를 일괄 삭제하고 싶다
		/*for (vector<int>::iterator it = v.begin(); it != v.end(); )
		{
			if ((*it % 2) != 0)
				it = v.erase(it);
			else
				++it;
		}*/
		v.clear();
		v.push_back(11);
		v.push_back(31);
		v.push_back(20);
		v.push_back(40);
		v.push_back(70);
		v.push_back(90);
		v.push_back(100);
		
		remove(v.begin(), v.end(), 20);
		remove_if(v.begin(), v.end(), IsOdd());
		v.erase(remove_if(v.begin(), v.end(), IsOdd()));
	}

	return 0;

}