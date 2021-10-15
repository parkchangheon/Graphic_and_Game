//계수 정렬

// 빠르긴하나, 데이터가 커지면 사용하기 어려워진다.
/*
#include<iostream>

using namespace std;

int main() {

	int temp;
	int count[6] = { 0, };
	int array[30] = {
		1,3,2,4,3,2,5,3,1,2,
		3,4,4,3,5,1,2,3,5,2,
		3,1,4,3,5,1,2,1,1,1
	};

	for (int i = 0; i < 30; i++) {
		temp = array[i];
		count[temp]++;
	}

	for (int i = 1; i < 6; i++) {
		cout << count[i] << " ";
	}


	for (int i = 1; i < 6; i++) {
		if (count[i] != 0)
		{
			for (int j = 0; j < count[i]; j++) {
				cout << i;
			}
		}
			
	}
}
*/
