//크루스칼 알고리즘


//#include<iostream>
//#include<stdio.h>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//int parent[8];
//
//class Edge {
//	int a, b, distance;
//public:
//	Edge(int a, int b, int distance) {
//		this->a = a;
//		this->b = b;
//		this->distance = distance;
//	}
//
//	bool operator <(Edge& edge) {
//		return this->distance < edge.distance;
//	}
//	void show() {
//		cout << distance << endl;
//	}
//};
//
//void lower(int parent[], int a, int b) {
//	if (parent[a] < parent[b])
//		parent[b] = parent[a];
//	else
//		parent[a] = parent[b];
//}
//
//
//
//int ifsame(int parent[], int a, int b) {
//	if (parent[a] == parent[b])
//		return 1;
//	return 0;
//}
//
//
//
//int main() {
//	int n = 7;
//	int m = 11;
//
//
//	for (int i = 1; i <= 7; i++) {
//		parent[i] = i;
//	}
//
//	vector<Edge> v;
//	v.push_back(Edge(1, 7, 12));
//	v.push_back(Edge(1, 4, 28));
//	v.push_back(Edge(1, 2, 67));
//	v.push_back(Edge(1, 5, 17));
//	v.push_back(Edge(2, 4, 24));
//	v.push_back(Edge(2, 5, 62));
//	v.push_back(Edge(3, 5, 20));
//	v.push_back(Edge(3, 6, 37));
//	v.push_back(Edge(4, 7, 13));
//	v.push_back(Edge(5, 6, 45));
//	v.push_back(Edge(5, 7, 73));
//
//	
//	sort(v.begin(), v.end());
//
//	for (int i = 0; i < v.size(); i++) {
//		v[i].show();
//	}
//
//
//
//}