// 동적 계획법 => 하나의 문제를 한번만 풀도록 하는 알고리즘
// 피보나치 수열이 대표적인 케이스 이며, 이는 앞에 물어봤던걸 다시 반복적으로 계산을 한다는 점에서 비효율 적이다


//DP 는 큰문제를 작은 문제로 나눌 수 있다.
//작은 문제에서 구한 정답은 그것을 포함하는 큰문제에서도 동일하게 사용 가능


/*
#include<iostream>
using namespace std;

int dp(int x) {
	if (x == 1)return 1;
	if (x == 2)return 1;
	return dp(x - 1) + dp(x - 2);
}




int main() {
	cout << dp(10);
}

*/
//비효율 ==> n번째 피보나치 수열을 구한다면, 2^n 의 연산을 진행해야한다.






/*
#include<iostream>
using namespace std;

int d[100];

int dp(int x) {
	if (x == 1)return 1;
	if (x == 2)return 1;
	if (d[x] != 0)return d[x];    //이런식으로 끼워 넣어 기록하는 방법을 쓴다 만약 있다면 끌어쓰고 없다면 계산해라.   //O(n) 의 복잡도가 든다.
	return dp(x - 1) + dp(x - 2);
}




int main() {
	cout << dp(30);
}

*/
