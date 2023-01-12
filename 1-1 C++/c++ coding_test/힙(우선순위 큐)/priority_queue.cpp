#include<iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
	vector<int> v = { 1, 2, 3, 9, 10, 12 };
	int K = 7;

	priority_queue<int, vector<int>, greater<int>> pq(v.begin(), v.end());
	int answer = 0;

	while (pq.size() > 1 && pq.top() < K)
	{
		int first = pq.top();
		pq.pop();
		int second = pq.top();
		pq.pop();

		pq.push(first + (second * 2));
		answer++;
	}

	if (pq.top() < K)
		return -1;

	return answer;

}