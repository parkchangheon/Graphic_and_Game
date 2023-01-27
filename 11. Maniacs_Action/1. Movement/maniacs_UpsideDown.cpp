#include "maniacs.h"
#include <iostream>


CReverseDirectMan::CReverseDirectMan() : speed(5.0f), flag(false),
X(0.f),Y(0.f),
get_Item(false)
{
	cout << "constructor." << endl;
}

bool CReverseDirectMan::Move(const CInputState* is)
{
	speed = 0.1f;
	
	if (flag)
		speed = -speed;

	if (is->Left()) X -= speed;
	if (is->Right()) X += speed;
	if (is->Up()) Y += speed;
	if (is->Down()) Y -= speed;
	
	// 
	if (X < 0) X = 0;
	if (X > MAX_X - 1) X = MAX_X - 1;
	//
	if (Y < 0) Y = 0;
	if (Y > MAX_Y - 1) Y = MAX_Y - 1;

	//아이템 획득 여부 판정
	//모든 아이템에 대하여 검사 + 아이템 획득 시 이동 방향이 바뀜
	for (CTaskIter i = Game->MoverList; i.HasNext(); )
	{
		CMover* mover = (CMover*)i.Next();

		//아이템이 일정 거리 안에 들어왔을때 아이템 획득 판정
		if (mover->Type == 1 && abs(mover->X - X) < 1 && abs(mover->Y - Y) < 1)
		{
			//이동방향을 반전 시킨다
			flag = !flag;
			i.Remove();

			get_Item = true;
		}
	}
	// -> 근데 리스트 


	// 아이템 삭제했다면, 새로운 아이템을 생성해준다.
	if (get_Item)
		new CReverseDirectMan();

	Angle = flag ? 0.5f : 0;
	return true;

}
