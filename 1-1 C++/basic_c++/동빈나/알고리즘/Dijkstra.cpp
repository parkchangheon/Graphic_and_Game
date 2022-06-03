// 선형 탐색으로 푸는 방법 ( O(n^2 ) 시간 복잡도가 걸림 )

//#include<iostream>
//using namespace std;
//
//int number = 6;
//int INF = 1000000000;
//
////전체 그래프 초기화
//int a[6][6] = {
//	{0,2,5,1, INF, INF},
//	{2,0,3,2,INF,INF},
//	{5,3,0,3,1,5},
//	{1,2,3,0,1,INF},
//	{INF,INF,1,1,0,2},
//	{INF,INF,5, INF,2,0}
//};
//bool v[6]; //방문 여부
//int d[6];  //최단 거리
//
////가장 최소 거리를 가지는 정점을 반환 
//int getSmallIndex() {
//	int min = INF;
//	int index = 0;
//	for (int i = 0; i < number; i++)
//	{
//		if (d[i] < min && !v[i]) {
//			min = d[i];
//			index = i;
//		}
//	}
//	return index;
//}
//
//
//// 다익스트라를 수행하는 함수입니다.
//void dijkstra(int start)//특정 정점에서 나가는...
//{
//	for (int i = 0; i < number; i++){
//		d[i] = a[start][i]; //특정정점에서 주변 노드들 삽입해준다.
//	}
//	v[start] = true; //지금 있는 노드 방문여부 체크
//	for (int i = 0; i < number - 2; i++) {
//		int current = getSmallIndex(); // 
//		v[current] = true; //현재 방문한 노드에 방문 처리를 해준다.
//		for (int j = 0; j < 6; j++) { 
//			if(!v[j]) //노드를 방문하지 않았다면,
//				if (d[current] + a[current][j] < d[j]) { //거쳐서 최종 노드까지 가는... 즉 현재 노드에서 최종 노드까지 가는 비용! 
//					d[j] = d[current] + a[current][j];
//				}
//		}
//	}
//}





// 힙의 특징을 사용하는 방법

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int number = 6;
int INF = 100000000;

vector<pair<int, int>> a[7];
int d[7];  //최소비용

void dijkstra(int start)
{
	d[start] = 0;
	priority_queue<pair<int, int>> pq;  //힙 구조를 사용합니다.

	//가까운 순서대로 처리하므로 큐를 사용합니다.
	while (!pq.empty())
	{
		int current = pq.top().first;
		//짧은 것이 먼저 오도록 음수화 시켜준다.
		int distance = -pq.top().second;
		pq.pop();

		//최단거리가 아닌 경우 스킵하도록 만듦
		if(d[current]<distance)
			continue;

		for (int i = 0; i < a[current].size(); i++)
		{
			//선택된 노드의 인접 노드
			int next = a[current][i].first;
			//선택된 노드 거쳐서 인접 노드로 가는 비용
			int nextDistance = distance + a[current][i].second;
			if (nextDistance < d[next]) {
				d[next] = nextDistance;
				pq.push(make_pair(next, -nextDistance));
			}

		}
	}

}