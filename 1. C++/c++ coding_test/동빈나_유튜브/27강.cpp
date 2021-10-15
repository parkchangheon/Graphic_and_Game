
//위상 정렬 
//사이클이 발생하면 안된다 -> 시작점이 반드시 존재 (진입점 진입차수가 0 이어야한다)

/*
#include<iostream>
#include<vector>
#include<queue>
#define MAX 10


using namespace std;

int n, inDegree[MAX]; //각 정점의 진입 차수 정보를 담고 있다
vector<int> a[MAX]; // 벡터값을 이용해서 노드에 연결된 정보를 담는다 


void topologySort() {
    int result[MAX];
    queue<int> q;


    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0)
            q.push(i);  // 진입차수가 0이라면 노드를 큐에 삽입한다.
    }


    // 위상정렬이 완전히 수행되려면 정확히 n개의 노드를 방문한다.
    for (int i = 1; i <= n; i++) {
        if (q.empty())
        {
            printf("사이클이 발생하였습니다");
            return;
        }
        int x = q.front();
        q.pop();

        result[i] = x;

        for (int i = 0; i < a[x].size(); i++) {
            int y = a[x][i];
            if (--inDegree[y] == 0) {
                q.push(y);
            }
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%d ", result[i]);
}

int main() {
    n = 7;
    a[1].push_back(2);
    inDegree[2]++;
    a[1].push_back(5);
    inDegree[5]++;
    a[2].push_back(3);
    inDegree[3]++;
    a[3].push_back(4);
    inDegree[4]++;
    a[4].push_back(6);
    inDegree[6]++;
    a[5].push_back(6);
    inDegree[6]++;
    a[6].push_back(7);
    inDegree[7]++;
    topologySort();
}

*/