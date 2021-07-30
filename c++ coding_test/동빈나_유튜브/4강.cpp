// 삽입 정렬
/*
#include<iostream>

using namespace std;

int main() {
	int arr[10] = { 1,65,2,4,11,53,23,54,66,90 };
	int i, j, temp;

	for (i = 0; i < 9; i++) {
		j = i;
		while (arr[j] > arr[j + 1]) {
			temp = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = temp;
			j--;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i]<<' ' ;
	}
}


//정렬이 되어있다고 가정을 한다.
//시간 복잡도는 O(N*N) 이긴 한데 최악 복잡도 일 경우.
*/


