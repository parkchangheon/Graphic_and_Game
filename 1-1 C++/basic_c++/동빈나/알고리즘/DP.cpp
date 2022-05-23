// 다이나믹 프로그래밍
// 문제를 단 한번만 풀도록 하는 알고리즘이다.
// 뭔가 트리같은 형태를 띄고 있는 것 같다.

// 큰문제를 작은 문제로 나눌 수 가 있다.
// 작은 문제에서 나온 정답을 큰문제에 사용 가능

//ex1) 피보나치 수열
//#include<iostream>
//using namespace std;
//
//int d[100];
//
//int dp(int x) {
//	if (x == 1)return 1;
//	if (x == 2)return 1;
//	if(d[x]!=0) return d[x]; //구한적 있는 값이면 그냥 리턴을 해주고
//	//구한적이 있다면
//	return d[x] = dp(x - 1) + dp(x - 2);  //이런식으로 재귀적으로 return 해줌
//}
//
//
//int main() {
//	cout << dp(30);
//}

//시간 복잡도가 n으로 줄어든다.


 //타일링 문제
//2*n 타일링 문제

//#include<iostream>
//using namespace std;
//
//int d[1001];
//int dp(int x)
//{
//	if (x == 1)return 1;
//	if (x == 2)return 2; //해당 일때 경우의 수를 써주면 된다.
//	if (d[x] != 0) return d[x];
//	return d[x] = (dp(x - 1) + dp(x - 2)) % 10007;
//}


//3*n일때 경우의 수  (1*2, 2*1)
// 1일때는 경우의 수가 없다. 2일때 생각을 해보자.
//3일때는 2가지 방법이 존재하고
//4일때는 특수한 경우가 두개 더있다.


//#include<iostream>
//using namespace std;
//
//int d[1001];
//int dp(int x)
//{
//	//짝수개일때마다 더 추가가 된다.
//	//홀수개일때는 값이 없다.
//	if (x == 0) return 1;
//	if (x == 1)return 0;
//	if (x == 2) return 3; //2인경우 경우의 수가 3개이다.
//	if (d[x] != 0)
//		return d[x];
//	int result = 3 * dp(x - 2); //그러므로 3* 를 해준다.
//	for (int i = 3; i <= x; i++)
//	{
//		if (i % 2 == 0)
//		{
//			result += (2 * dp(x - i));
//		}
//	}
//	d[x] = result;
//	return d[x];
//}



//타일 채우기 3
//타일의 종류가 3가지 (2*n을 1*2, 2*1, 1*1로 채우기) 

//#include<iostream>
//using namespace std;
//
//int d[1000001];
//int dp(int x)
//{
//	//짝수개일때마다 더 추가가 된다.
//	//홀수개일때는 값이 없다.
//	if (x == 0) return 1;
//	if (x == 1)return 2;
//	if (x == 2) return 7; //2인경우 경우의 수가 7개이다.
//
//	long result = 3 * dp(x - 2) + 2 * dp(x - 1);
//	for (int i = 3; i <= x; i++)
//	{
//		result += (2 * dp(x - i)) % 1000007;
//	}
//	return d[x] = result % 1000007;
//}
// 비효율적이다!!!!!!




//2차원 DP 개념

//#include<iostream>
//using namespace std;
//
//int d[1000001][2];
//
//int dp(int x) {
//	d[0][0] = 0;
//	d[1][0] = 2;
//	d[2][0] = 7;
//	d[2][1] = 1;
//
//	for (int i = 3; i <= x; i++) {
//		d[i][1] = (d[i - 1][1] + d[i - 3][0]) % 1000007;
//		d[i][0] = (3 * d[i - 2][0] + 2 * d[i - 3][0] + 2) % 1000007;
//	}
//	return d[x][0];
//}
