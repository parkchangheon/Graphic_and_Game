#include "8-9.h"
#include<iostream>
using namespace std;


int main() {

	cout << "**** 한성학공에 오신것을 환영합니다 ****" << endl;
	while (true)
	{
		int selecter;

		reservation* r = new reservation();
		seat* s = new seat();


		cout << "예약 : 1, 취소 : 2, 보기 : 3, 끝내기 : 4 >> ";
		cin >> selecter;

		if (selecter == 4)
			break;

		else if (selecter == 2)
			continue;

		else if (selecter == 3)
		{
			s->seat_show();
		}
		else if (selecter == 1)
		{
			int time_selecter;
			cout << " 07시 :1, 12시 :2, 17시 :3 >> ";
			cin >> time_selecter;

			s->plane_seat(time_selecter);

			int seat_number;
			string name;
			cout << "좌석 번호 >> ";
			cin >> seat_number;

			cout << "이름 입력 >> ";
			cin >> name;

			s->set_seat(time_selecter - 1, seat_number, name);


		}
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}

	}
}