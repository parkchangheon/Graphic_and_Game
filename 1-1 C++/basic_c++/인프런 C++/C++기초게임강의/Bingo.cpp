/*

#include<iostream>
#include<time.h>
using namespace std;


int main() {
	srand((unsigned int)time(0));
	int iNumber[25] = {};

	//1~25까지 숫자를 넣어준다.
	for (int i = 0; i < 25; ++i) {
		iNumber[i] = i + 1;
	}

	//숫자 섞어주기
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	for (int i = 0; i < 25; i++) {
		cout << iNumber[i] <<' ';
	}

	int Bingo = 0;

	while (true) {
		system("cls"); //지운다.

		//숫자를 5*5로 출력한다.
		for (int i = 0; i < 5; ++i) {

			for (int j = 0; j < 5; ++j) {
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << '\t';
			}


			cout << endl;
		}


		cout << "Bingo Line : " << Bingo << endl;

		cout << "숫자를 입력하세요 : (0은 종료) : ";
		int input;
		cin >> input;

		if (input == 0)
			break;

		else if (input < 0 && input>25)
			continue;


		bool flag = true;

		for (int i = 0; i < 25; i++) {
			if (input == iNumber[i]) {
				flag = false;

				iNumber[i] = INT_MAX;
				//더 이상 다른 숫자를 찾아볼 필요가 없어 빠져나감
				break;
			}
		}

		if (flag)
			continue;

		//빙고 줄 수를 체크하는 것은 매번 숫자를 입력할때마다 처음부터 새로 카운트를 한다. 그러므로 BIngo 변수를 매번 초기화 해준다.
		Bingo = 0;

		//가로, 세로, 줄 수를 구해준다
		int iCheck1 = 0, iCheck2 = 0;
		for (int i = 0; i < 5; ++i) {

			iCheck1 = iCheck2 = 0;
			for (int j = 0; j < 5; ++j) {
				//가로 별 개수를 구해준다.

				if (iNumber[i * 5 + j] == INT_MAX)
					++iCheck1;


				if (iNumber[j * 5 + i] == INT_MAX)
					++iCheck2;
			}

			if (iCheck1 == 5)
				++Bingo;

			if (iCheck2 == 5)
				++Bingo;
		}
		// 대각선 하나
		iCheck1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;
		}

		if (iCheck1 == 5)
			++Bingo;


		iCheck1 = 0;

		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;
		}

		if (iCheck1 == 5)
			++Bingo;
	}

	return 0;
}

*/






