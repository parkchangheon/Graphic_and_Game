// 백준 문제 타일링

// 2*n의 문제 

// 점화식이 d[i] = d[i-1]+d[i-2] 인 문제
/*
#include<iostream>
using namespace std;
int d[1001];

int dp(int x) {
	if (x == 1)
		return 1;
	
	if (x == 2)
		return 2;

	if (d[x] != 0)return d[x];
	return d[x] = (dp(x - 1) + dp(x - 2)) % 10007;  // 메모이제이션 기법
}


int main() {
	cout << dp(9);
}
*/








// 점화식이 d[i] = d[i-1]+2*d[i-2] 인 문제
/*
#include<iostream>
using namespace std;
int d[1001];

int dp(int x) {
	if (x == 1)
		return 1;

	if (x == 2)
		return 3;

	if (d[x] != 0)return d[x];
	return d[x] = (dp(x - 1) + 2*dp(x - 2)) % 10007;  // 메모이제이션 기법
}


int main() {
	cout << dp(9);
}
*/



