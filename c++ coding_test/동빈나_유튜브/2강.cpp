//선택정렬 

/*
#include<iostream>

using namespace std;

int main() {
	int i, j, min, index, temp;
	int arr[10] = { 4,3,5,1,2,9,8,7,6,10 };
	for (int i = 0; i < 10; i++) {
		min = 99999;
		for (int j = i; j < 10; j++) {
			if (arr[j] < min)
			{
				min = arr[j];
				index = j;
			}
		}
		temp = arr[i];
		arr[i] = min;
		arr[index] = temp;
	}

	for (int i = 0; i < 10; i++) {
		cout << arr[i] << ' ';
	}
}

*/
// 선택 정렬은 시간 복잡도 
// =>10 9 8 7 6 5 4 3 2 1 ==> n(n+1)/2 =>O(n^2)