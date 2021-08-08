// 퀵 정렬 
/*
#include<iostream>
using namespace std;

int arr[10] = { 3,7,8,1,5,9,6,10,2,4 };
int num = 10;

void quickSort(int* data, int start, int end) {
	if (start > end)
		return;

	int key = start; // 키는 첫번째 요소
	int i = start + 1;
	int j = end;
	int temp;

	while (i <= j) {
		while (data[i] <= data[key]) {
			i++;
		}
		while (data[j] >= data[key] && j>start)
		{
			j--;
		}

		if (i > j) {
			temp = data[j];
			data[j] = data[key];
			data[key] = temp;
		}
		else {
			temp = data[j];
			data[j] = data[i];
			data[i] = temp;
		}
	}

	quickSort(data, start, j - 1);
	quickSort(data, j + 1, end);

}



int main() {
	quickSort(arr, 0, num - 1);
	for (int i = 0; i < 10; i++) {
		cout << arr[i] << ' ';
	}
}

*/


//재귀 함수를 쓰는것이 POINT

// 분할  정복 기법을 이용하므로, O(NlogN) 의 시간 복잡도를 가지는데, 
// 최악의 시간복잡도는 O(N*N)이다.   => 피벗값이 잘못 설정될때. ==> 이미 정렬이 되어있는 경우

//1 2 3 4 5 6 7 8 9 10 이렇게 되어있다면,
//1 은 이미 정렬 그럼 나머지 2~10을 다시 정렬 하므로, 분할 정렬의 이점을 전혀 사용하지 못함. ==>N^2