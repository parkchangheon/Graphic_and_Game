//∆Î±œ√ﬂ∂Ù¥Î√•¿ßø¯»∏

#include<iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int* arr = new int[N];
	int pen=0;  //∆Î±œ¿Ã ¿÷¥¬ ¿Œµ¶Ω∫
	int right = 0; 
	int left = 0;
	int min1=1000000000;
	int min0 = 1000000000;

	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		arr[i] = tmp;
		if (tmp == -1) {
			pen = i;
		}
	}
	right = left = pen;

	while (right < N || left > 0)
	{
		if (right < N)
		{
			right++;
			if (right < N && arr[right] < min1)
				min1 = arr[right];
		}

		if (left > 0)
		{
			left--;
			if (arr[left] < min0)
				min0 = arr[left];
		}
	}
	cout << min0 + min1;
}





//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//int N, n[200000] = {}, p, l_m = 1000000001, r_m = 1000000001;
//int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin >> N;
//	
//	for (int i = 0; i < N; i++) {
//		cin >> n[i];
//		if (n[i] == -1)
//			p = i;
//	}
//
//	for (int i = 0; i < p; i++)
//		l_m = min(l_m, n[i]);
//	for (int i = p + 1; i < N; i++)
//		r_m = min(r_m, n[i]);
//	cout << l_m + r_m;
//}