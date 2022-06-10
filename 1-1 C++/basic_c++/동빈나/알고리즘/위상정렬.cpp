//위상정렬

//#include<iostream>
//#include<vector>
//#include<queue>
//
//#define MAX 32001
//
//using namespace std;
//
//int n, inDegree[MAX], result[MAX];  //진입 차수와 결과 반환
//vector<int> a[MAX];  //정점마다 연결되어 있는 간선
//
//void topologySort() {
//	queue<int> q;
//	//진입 차수가 0인 노드를 큐에 삽입한다.
//	for (int i = 1; i <= n; i++) {
//		if (inDegree[i] == 0) {
//			q.push(i);
//		}
//	}
//
//	//정렬이 완전히 수행되려면 정확히 n개의 노드를 방문한다.
//	for (int i = 1; i <= n; i++) {
//		int x = q.front();
//		q.pop();
//		result[i] = x;
//		for (int j = 0; j < a[x].size(); j++) {
//			int y = a[x][j];
//			//새롭게 진입차수가 0이 된 정점을 큐에 삽입한다.
//			if (--inDegree[y] == 0) {
//				q.push(y);
//			}
//		}
//	}
//
//	for (int i = 1; i <= n; i++) {
//		cout << result[i] << ' ';
//	}
//}
//
//int main()
//{
//	int m;
//	cin >> n >> m;
//	for (int i = 0; i < m; i++) {
//		int x, y;
//		cin >> x >> y;
//		a[x].push_back(y);
//		inDegree[y]++;
//	}
//	topologySort();
//}
