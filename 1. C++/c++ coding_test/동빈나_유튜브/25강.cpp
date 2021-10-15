//25강 다익스트라 (GPS, 인공위성에서 주로 쓰임)

/*
//배열을 하나 써서 거쳐가고 갱신하는...
#include<iostream>
using namespace std;

int number = 6;
int INF = 100000000;


//전체 그래프를 초기화 한다.

int a[6][6] = {
	{0,2,5,1,INF,INF},
	{2,0,3,2,INF,INF},
	{5,3,0,3,1,5},
	{1,2,3,0,1,INF},
	{INF,INF,1,1,0,2},
	{INF,INF,5,INF,2,0}
};

bool v[6]; //방문되었는지에 대한 
int  d[6]; // 방문노드 거리 (최단 거리)


//가장 최소의 거리를 가지는 정점을 반환
int getSmallIndex() {
	int min = INF;
	int index = 0;
	for (int i = 0; i < number; i++) {
		if (d[i] < min && !v[i]) {
			min = d[i];
			index = i;
		}
	}
	return index;
}





// 다익스트라를 수행하는 함수
void dijkstra(int start) {
	for (int i = 0; i < number; i++) {
		d[i] = a[start][i];
	}
	v[start] = true;
	for (int i = 0; i < number - 2; i++) {
		int current = getSmallIndex();
		v[current] = true;
		for (int j = 0; j < 6; j++) {
			if (!v[j]) {
				if (d[current] + a[current][j] < d[j]) {
					d[j] = d[current] + a[current][j];
				}
			}
		}
	}
}

int main() {
	dijkstra(0);
	for (int i = 0; i < number; i++) {
		cout << d[i]<<" ";
	}
}
*/
