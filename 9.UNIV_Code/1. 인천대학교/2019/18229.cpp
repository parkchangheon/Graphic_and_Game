//내가 살게 아냐 내가 살게

#include<iostream>
using namespace std;

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	int temp[100] = { 0, };
	int arr[100][100];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> arr[i][j];
		}
	}

	int turn = 0;
	while (1)
	{
		for (int i = 0; i < n; i++)
		{
			temp[i] += arr[i][turn];
			if (temp[i] >= k) {
				cout << i + 1 << " " << turn + 1;
				exit(0);
			}
		}
		++turn;
	}
}