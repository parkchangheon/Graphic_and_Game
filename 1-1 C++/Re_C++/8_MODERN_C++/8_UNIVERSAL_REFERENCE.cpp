#include<list>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

class Knight {
public:
	Knight() { cout << "기본 생성자" << endl; }
	Knight(const Knight& knight) { cout << "복사 생성자" << endl; };
	Knight(Knight&&)noexcept { cout << "이동 생성자" << endl; };
};

void Test_RValueReference(Knight&& knight)
{

}

template<typename T>
void Test_ForwardingRef(T&& param)    //전달참조이다. (왼값을 넣으면 왼값, 오른값을 넣으면 오른값) 하지만 const T&& param 되는 순간 오른값 참조처럼 사용된다.
{
	//아래 두 기능을 알아서 자동으로 해줌. (왼값 참조면 복사, 오른값 참조면 이동 해줘~ 
	TestCopy(std::forward<T>(param));
	
	//TestCopy(param); //왼값참조 ver ( 복사 ) 
	//TestCopy(std::move(param)); //오른값 참고 ver ( 이동 )

}

void TestCopy(Knight&& knight)
{


}


int main()
{
	//보편 참조 ( universal_reference)
	//전달 참조 (forwarding_reference)  c++17

	Knight k1;
	Test_RValueReference(std::move(k1));
	Test_ForwardingRef(std::move(k1));
	Test_ForwardingRef(k1); //원래는 안될거같은데 된다!!?    ==> 위에서 template로 받아주기 때문

	auto&& k2 = k1;   //얘도 왼값이다.
	auto&& k3 = std::move(k1); //얘는 오른값이다.


	Knight& k4 = k1;             //왼값참조
	Knight&& k5 = std::move(k1); //오른값 참조


	//오른값 : 왼값이 아닌 것 = 단일식에서 벗어나면 사용이 불가능하다.
	//오른값 참조 : 오른값만 참조할 수 있는 참조 타입
	Test_RValueReference(std::move(k5));  //k4, k5 둘다 안된다? ==> k4는 원래 왼값이기 때문에 당연히 안되는데, k5는 왜 안될까?
	//k5는 오른값 참조 타입이긴 한데, 단일식을 벗어나도 사용이 가능하다.... 결국 오른값 참조 타입이긴한데, k5 자체는 왼값이라는 문제가 있다. 
	//그래서 std::move로 받아줘야한다...



}