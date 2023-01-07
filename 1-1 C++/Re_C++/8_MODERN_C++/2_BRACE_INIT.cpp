//#include<list>
//#include<deque>
//#include<map>
//#include<set>
//#include<algorithm>
//#include<iostream>
//#include<vector>
//#include<map>
//
//using namespace std;
//
//
//class Knight
//{
//public:
//	Knight()
//	{
//		cout << "basic inti" << endl;
//	}
//
//	Knight(int a, int b) {
//		cout << a << "," << b << endl;
//	}
//
//	Knight(initializer_list<int> li)  
//	{
//		cout << "initializer_list inti" << endl;
//	}
//};
//
//
//int main()
//{
//	//중괄호 초기화
//	int a = 0;
//	int b(0);
//	int c = { 0 };
//
//	Knight k1;
//	Knight k2 = k1; //대입연산자 x 
//	Knight k3; 
//	k3 = k1; //대입연산자o
//
//	//1) 컨테이너와도 잘어울림
//	int arr[] = { 1,2,3,4 };
//	vector<int> v2(10, 1); //기존 초기화 
//	vector<int> v3{ 1,2,3,4 };
//
//	//2)
//	int x = 0;
//	double y(x); //이렇게 빌드해도 문제는 없는데, 완전히 호환되는게 아니라 데이터 손실이 가능하다.
//	//==>
//	double y{ x };
//
//	//3)
//	Knight k4{};
//	Knight k5{ 1,2,3,4,5 };  //이렇게 받아주고 싶다면 어떻게 해야할까? ==> 위처럼 initializer_list를 받아준다.
//
//	//ex) 
//	Knight k_test{ 1,2 }; //이렇게 하면 과연 생성자는 어떤것이 호출될까. initializer_list일까? or int int 일까 
//	//==> initializer_list가 우선권을 가져간다. (근데 다른 생성자를 먹을정도로, initializer_list가 먹기에 마냥 좋진 않다.)
//
//
//	return 0;
//}