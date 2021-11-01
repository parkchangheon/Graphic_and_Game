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






/*
#include<iostream>
#include<time.h>
using namespace std;

enum AI_MODE {
	AM_EASY=1,
	AM_HARD
};


int main() {
	srand((unsigned int)time(0));
	int iNumber[25] = {};
	int AiNumber[25] = {};

	//1~25까지 숫자를 넣어준다.
	for (int i = 0; i < 25; ++i) {
		iNumber[i] = i + 1;
		AiNumber[i] = i + 1;

	}

	//숫자 섞어주기
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;

		//ai 숫자도 섞어준다.

		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = AiNumber[idx1];
		AiNumber[idx1] = AiNumber[idx2];
		AiNumber[idx2] = iTemp;
	}


	int Bingo = 0,AiBingo=0;

	int Aimode;
	
	//ai 난이도를 선택한다.
	while (true) {
		system("cls");
		cout << "1.Easy" << endl;
		cout << "2.Hard" << endl;
		cout << "Ai 모드를 선택하세요";
		cin >> Aimode;

		if (Aimode>=AM_EASY || Aimode<=AM_HARD)
			break;
	}

	
	//Ai Easy 모드는 현재 AI의 숫자 목록중 * 로 바뀌지 않는 숫자 목록을 만들어서 그중 하나를 바꾸는 거고, HARD는 해당 줄에 있는 것을 바꾼다.
	

	// 선택 안된 목록 배열
	int NoneSelect[25] = {};
	//선택 안된 숫자 개수를 저장한다
	int NoneSelectCount = 0;

	while (true) {
		system("cls"); //지운다.

		//숫자를 5*5로 출력한다.
		cout << "=================Player====================" << endl;
		for (int i = 0; i < 5; ++i) {

			for (int j = 0; j < 5; ++j) {
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << '\t';
			}
			cout << endl;
		}


		cout << "Bingo Line : " << Bingo << endl<<endl;
		cout << "================= Ai ====================" << endl;


		switch (Aimode) {
		case AM_EASY:
			cout << "AIMODE : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AIMODE : HARD" << endl;
			break;
		}

		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (AiNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << AiNumber[i * 5 + j]<<"\t";
			}
			cout << endl;
		}

		//ai 빙고 줄 수를 출력한다.
		cout << "AiBingo Line = " << AiBingo << endl;

		if (Bingo >= 5)
		{
			cout << "Player 승리" << endl;
			break;
		}

		else if (AiBingo >= 5) {
			cout << "Ai 승리" << endl;
			break;
		}

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

		for (int i = 0; i < 25; ++i)
		{
			if (AiNumber[i] == input)
			{
				AiNumber[i] = INT_MAX;
				break;
			}
		}


		//ai 가 선택한다. (모드에 따라 달라짐)
		switch (Aimode) {
		case AM_EASY:
			// 선택 안된 숫자 목록 만들기
			NoneSelectCount = 0;

			for (int i = 0; i < 25; i++) {
				if (AiNumber[i] != INT_MAX)
				{
					//*이 아닌 숫자일 경우 NoneSelectCount를 인덱스로 활용한다. 선택 안된 목록에 추가할때마다 개수를 1씩 증가시켜서 총 선택 안된 개수를 구해준다.    0~ 카운트 추가.
					NoneSelect[NoneSelectCount] = AiNumber[i];
					++NoneSelectCount;
				}
			 }
			//목록 보여주기 => 선택 안된 목록의 숫자중 랜덤한 하나의 숫자를 얻어 오기 위한 코드
			input = NoneSelect[rand() % NoneSelectCount];
			break;
			
		case AM_HARD:
			break;

		}

		//AI가 선택한 숫자를 *로 바꿔준다
		for (int i = 0; i < 25; ++i) {
			if (iNumber[i] == input) {
				iNumber[i] = INT_MAX;
				break;
			}
		}

		//AI가 선택한 숫자를 바꿔준다
		for (int i = 0; i < 25; ++i) {
			if (AiNumber[i] == input) {
				AiNumber[i] = INT_MAX;
				break;
			}
		}




		//빙고 줄 수를 체크하는 것은 매번 숫자를 입력할때마다 처음부터 새로 카운트를 한다. 그러므로 BIngo 변수를 매번 초기화 해준다.
		Bingo = 0;
		AiBingo = 0;


		//가로, 세로, 줄 수를 구해준다
		int iCheck1 = 0, iCheck2 = 0;
		int iAiCheck1 = 0, iAiCheck2 = 0;

		for (int i = 0; i < 5; ++i) {

			iCheck1 = iCheck2 = 0;
			iAiCheck1 = iAiCheck2 = 0;

			for (int j = 0; j < 5; ++j) {
				//가로 별 개수를 구해준다.

				if (iNumber[i * 5 + j] == INT_MAX)
					++iCheck1;


				if (iNumber[j * 5 + i] == INT_MAX)
					++iCheck2;

				if (AiNumber[i * 5 + j] == INT_MAX)
					++iAiCheck1;

				if (AiNumber[j * 5 + i] == INT_MAX)
					++iAiCheck2;
			}

			if (iCheck1 == 5)
				++Bingo;

			if (iCheck2 == 5)
				++Bingo;

			if (iAiCheck1 == 5)
				++AiBingo;

			if (iAiCheck2 == 5)
				++AiBingo;
		}
		// 대각선 하나
		iCheck1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;

			if (AiNumber[i] == INT_MAX)
				++iAiCheck1;
		}

		if (iCheck1 == 5)
			++Bingo;

		if (iAiCheck1 == 5)
			++AiBingo;


		iCheck1 = 0;
		iAiCheck1 = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;

			if (AiNumber[i] == INT_MAX)
				++iAiCheck1;
		}

		if (iCheck1 == 5)
			++Bingo;

		if (iAiCheck1 == 5)
			++AiBingo;
	}

	return 0;
}


*/


