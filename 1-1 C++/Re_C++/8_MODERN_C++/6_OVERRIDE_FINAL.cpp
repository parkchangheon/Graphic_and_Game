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
//class Player
//{
//public:
//	virtual void Attack()
//	{
//		cout << "Player" << endl;
//	}
//};
//
//class Knight : public Player
//{
//public:
//	//void Attack() // 그럼 이 Attack을 최초로 만든애가 누구일지!? (프로젝트가 점점 커짐에 따라)
//	//{
//	//	cout << "Knight" << endl;
//	//}
//	
//	//void Attack() const //이렇게 만들면, Knight의 Attack이 Player의 Attack과 별개로 자신이 시초인듯 만들어서 행동함.
//	//{
//	//	cout << "Knight_const" << endl;
//	//}
//
//	//void Attack() override // 이렇게 만들면 부모로 부터 상속받은거다~ 라고 안전하게 만듦.
//	//{
//	//	cout << "Knight_override" << endl;
//	//}
//
//	void Attack() final //이렇게 만들면, Knight를 마지막으로 내가 상속받는다고 알려줌.
//	{
//		cout << "Knight_final" << endl;
//	}
//};
//
//int main()
//{
//	Knight* knight = new Knight(); 
//	knight->Attack();
//
//	Player* player = new Knight();
//	player->Attack(); //해도 casting하면 써먹을 수는 있다. => Player가 뜬다. 포인터 타입이 player이므로
//
//	//그러므로 가상함수화해준다.
//
//
//	return 0;
//}