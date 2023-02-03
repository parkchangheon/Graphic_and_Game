#include<iostream>
using namespace std;

// 1) 주소 연산자 (&)
// 2) 산술 연산자 (+ -)
// 3) 간접 연산자 (*)
// 4) 간접 멤버 연산자 

class Player
{
public:
	int hp;  // +0
	int damage; // +4
};

Player globalInfo;

void PrintInfoPTR(Player* player)
{
	player->hp = 10;
	player->damage = 5;
	
	//포인터는 *을 기준으로 앞에 붙이냐 뒤에 붙이냐에 따라 const의미가 달라짐.
	//주소값 자체가 변경이 되지 않게 하느냐   vs    전달되어온 데이터를 변경 되지 않게 하냐
	//ex)
	player = &globalInfo; //주소값을 바꾼다
	player->hp = 1000;


	//*앞에 붙인다면    ==> 가져온 데이터를 바꾸지 못한다.
	/*const Player* player;*/


	//*뒤에 붙인다면    ==> 주소값을 바꾸지 못함.
	/*Player* const player;*/
	
}


void PrintInfoREF(const Player& player)
{
	//const 를 붙이면 수정이 불가능
	//player.hp = 11;
	//player.damage = 6;
}


int main()
{
	int number = 1;
	int number2 = 2;

	// 1) 주소 연산자 (&)
	// - 해당 변수의 주소를 알려주라
	int* pointer = &number;


	//2) 산술 연산자 (+-)
	pointer += 1;
	// 포인터에서 + - 등 산술 연산으로 1을 더하거나 뺴면
	// 정말 그 숫자를 더하고 빼는 것이 아닌 타입 크기만큼 이동


	//3) 간접 연산자 (*)
	// - 포탈을 타고 해당 주소로 순간이동
	number = 3;
	*pointer = 4;

	Player player;
	player.hp = 100;
	player.damage = 10;

	Player* playerptr = &player;
	(*playerptr).hp =100;


	// 4) 간접 멤버 연산자 (->)
	playerptr->hp = 200;
	playerptr->damage = 20;



	
	//참조전달 방식
	int& reference = number;
	//참조 쓰는 이유? => 참조 전달때문에 쓴다
	//전달이후에 . 을 사용해서 손쉽게 사용이 가능하기 때문에
	Player& reference2 = player;


	Player info;

	//포인터 형식
	PrintInfoPTR(&info);

	//참조 형식
	PrintInfoREF(info);


	//참조는 null을 사용불가 포인터는 nullptr을 사용가능
	// null check에 유용하다.


	// - 없는 경우도 고려해야한다면, nullptr (널체크)
	// - 바뀌지 않고 읽는 용도(readOnly)만 사용한다면 const ref&
	// - 그 외 일반적으로 ref (명시적으로 호출할 때 OUT을 붙인다)


	//포인터로 사용하던걸 참조로 넘겨주려면?
	PrintInfoREF(*playerptr);

	//참조로 사용하던걸 포인터로 넘겨주려면
	PrintInfoPTR(&reference2);
	return 0;
}