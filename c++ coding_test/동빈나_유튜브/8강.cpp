/*
//8강 합병 정렬

//일단 반으로 쪼개고 나중에 합친다.
//NlogN

#include<iostream>
using namespace std;

int num = 8;
int sorted[8]; // 정렬 배열은 반드시 전역 변수로 

void merge(int a[], int m, int middle, int n) {
	int i = m; // 왼쪽 배열 시작점 
	int j = middle + 1; // 오른쪽 배열 시작점

	int k = m; // 합칠 배열의 맨 왼쪽 인덱스를 가리킴

	while (i <= middle  && j <= n) {  // 각 left, right를 끝점 까지 반복
		if (a[i] <= a[j]) {
			sorted[k] = a[i];
			i++;
		}
		else {
			sorted[k] = a[j];
			j++;
		}
		k++; // 합친 값 인덱스 증가시켜줌
	}
	//남은 데이터들도 삽입
	if (i > middle) {  //i가 먼저 끝났다면 현재 j부터 뒤는 쭈욱
		for (int t = j; t <= n; t++) {
			sorted[k] = a[t];
			k++;
		}
	}
	else { //j가 먼저 끝났다면
		for (int t = i; t <= middle; t++) {
			sorted[k] = a[t];
			k++;
		}
	}

	for (int t = m; t <= n; t++) {
		a[t] = sorted[t];
	}
}

void mergeSort(int a[], int m, int n) {
	if (m < n) {
		int middle = (m + n) / 2;
		mergeSort(a, m, middle);
		mergeSort(a, middle+1, n);
		// 나누는 과정... 그리고 병합
		merge(a, m, middle, n);
	}
}

int main() {
	int arr[8] = { 7,6,5,8,3,5,9,1 };
	mergeSort(arr, 0, num - 1);

	for (int i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
}
*/
