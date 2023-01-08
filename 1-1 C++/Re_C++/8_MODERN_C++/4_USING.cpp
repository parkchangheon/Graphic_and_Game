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
//typedef __int64 id;
//using id2 = int;
//
//// 1) 직관성
//typedef void (*MyFunc)();
//using MyFunc2 = void(*)();
//
////2) 템플릿 
//template<typename T>
//using List = std::list<T>;
//
////template<typename TT>
////typedef std::vector<TT> List2; //에러 발생
////-> typedef는 템플릿을 사용하지 못한다.
//
//
//int main()
//{
//	id player = 0;
//	List<int> li;
//	li.push_back(1);
//	li.push_back(2); //....
//}