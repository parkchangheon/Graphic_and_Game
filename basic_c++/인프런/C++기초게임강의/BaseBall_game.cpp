/*
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	int arr[3];
	int data[10];

	for (int i = 0; i < 10; i++) {
		data[i] = i;
	}

	for (int i = 0; i < 3; i++) {
		arr[i] = rand() % 9 + 1;
		for (int j = 0; j < i; j++)
		{
			if (arr[i] == arr[j]) {
				i--;
				break;
			}
		}
	}



	cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << endl;

	int out, strike, ball;
	out = strike = ball = 0;

	int compare[3];

	while (strike != 3) {
		out = strike = ball = 0;

		cin >> compare[0] >> compare[1] >> compare[2];

		if (compare[0] == 0 || compare[1] == 0 || compare[2] == 0) {
			break;
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i==j&&arr[i] == compare[j]) {
					strike += 1;
				}
				else if (arr[i] == compare[j]) {
					ball += 1;
				}
			}

		}
		cout << "strike = " << strike << " ball = " << ball << " out = " << 3 - strike - ball;

		if (strike == 3)
			break;

		
	}

}

*/