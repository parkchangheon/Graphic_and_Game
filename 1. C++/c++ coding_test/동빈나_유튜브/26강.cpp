// 플로이드 와샬 알고리즘

// 다익스트라의 경우는 한 노드에서 다른 노드까지의 거리를 1차원 배열을 통해 이동하는 것을 시각화 



// 1을 거쳐서 가는 경우 ( 2->3 , 2->4 , 3->2 , 3->4 , 4->2, 4->3 ) 
// ex) 2->3 으로 가는 비용과, 2->1 + 1->3 으로 가는 비용을 비교한다.   9 vs 7 +무한.    그럼 1을 거쳐가는 비용이 더 크므로 갱신 x 

// ... 이런식으로 1, 2, 3, 4 를 거쳐가는 비용을 계산한다.

/*

#include<iostream>
#include<stdio.h>
using namespace std;

int number = 4;
int inf = 10000000;

int a[4][4] = {
	{0,5,inf,8},
	{7,0,9,inf},
	{2,inf,0,4},
	{inf,inf,3,0}
};

void floydWarshall() {
	//결과 배열을 초기화 해준다.
	int** d = new int* [number];
	for (int i = 0; i < number; ++i) {
		d[i] = new int[number];
	}

	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			d[i][j] = a[i][j];
		}
	}


	//k는 거쳐가는 노드 
	for (int k = 0; k < number; k++) {
		// i 는 출발 노드
		for (int i = 0; i < number; i++) {
			// j 는 도착 노드
			for (int j = 0; j < number; j++) {
				if (d[i][k] + d[k][j] < d[i][j])
					d[i][j] = d[i][k] + d[k][j];

			}
		}
	}

	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
}

int main() {
	floydWarshall();
}


*/




