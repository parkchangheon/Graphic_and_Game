//스타크래프트 건물 알고리즘 (위상정렬 사용)
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define MAX 501
int n, inDegree[MAX], tt[MAX], result[MAX];
vector<int> a[MAX];

void topology()
{
	queue<int> q;
	for (int i = 1; i <= n; i++)
	{
		if (inDegree[i] == 0) {
			result[i] = tt[i];
			q.push(i);
		}
	}

	for (int i = 1; i <= n; i++) {
		int x = q.front();
		q.pop();

		for (int j = 0; j < a[x].size(); j++) {
			int y = a[x][j];
			result[y] = max(result[y], result[x] + tt[y]);

			if (--inDegree[y] == 0) {
				q.push(y);
			}
		}
	}
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> tt[i];        //걸리는 시간 입력받아준다.
		while (1) {
			int x;
			cin >> x;
			if (x == -1) break;  // 끝날때까지 선행조건 넣어준다.

			inDegree[i]++;    //진입차수 늘려준다.
			a[x].push_back(i);
		}
	}
}