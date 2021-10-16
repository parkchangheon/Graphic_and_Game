// Union Find 합집합 찾기 => 서로소 찾기
// 값을 합칠떄, 부모를 자기보다 더 작은 값으로 설정하여, 연결 (연결이 안된 상태에서는 자기자신을 부모로 갖는다)
// 재귀함수를 사용하여, 자신이 부모로 갖는 값을 갱신해준다.

/*

#include<iostream>

using namespace std;


int getparent(int parent[], int x) {
	//재귀함수의 종료 부분
	if (parent[x] == x)
		return x;

	//현재 가리키고 있는 부모노드가 달라, 실질 노드 찾기 위한 과정
	return parent[x] = getparent(parent, parent[x]);
}


//두 부모 노드를 합치는 함수
int unionParent(int parent[], int a, int b) {
	a = getparent(parent, a);
	b = getparent(parent, b);

	if (a < b)
		return parent[b] = a;
	else 
		return parent[a] = b;
}



//같은 부모를 가지는지 확인
int findParent(int parent[], int a, int b) {
	a = getparent(parent, a);
	b = getparent(parent, b);

	if (a == b)
		return 1;
	else
		return 0;
}


int main() {
	int parent[11];
	for (int i = 1; i <= 10; i++) {
		parent[i] = i;
	}

	unionParent(parent, 1, 2);
	unionParent(parent, 2, 3);
	unionParent(parent, 3, 4);
	unionParent(parent, 5, 6);
	unionParent(parent, 6, 7);
	unionParent(parent, 7, 8);

	printf("1과 5는 연결되어 있나요?? %d \n", findParent(parent, 1, 5));
}
*/

















