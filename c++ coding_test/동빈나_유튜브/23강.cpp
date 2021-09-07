// 또다른 점화식

//이번엔 길이가 3(홀수)일때


// 일일히 해보는 수밖에 없다.
// 점화식이 D[n] = 3*D[n-2] + 2*(D[n-4]+D[n-6]...+D[0])



/*
#include<iostream>
using namespace std;
int d[1001];

int dp(int x) {
	if (x == 0)return 1;
	if (x == 1)return 0;
	if (x == 2)return 3;
	if (d[x] != 0)return d[x];

	int result = 3 * dp(x - 2);  // 메모이제이션 기법
	for (int i = 3; i <= x; i++) {
		if (i % 2 == 0) {
			result += 2 * dp(x - i);
		}
	}
}


int main() {
	cout << dp(2);
}
*/




