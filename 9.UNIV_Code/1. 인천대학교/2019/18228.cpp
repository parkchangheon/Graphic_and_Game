//Æë±ÏÃß¶ô´ëÃ¥À§¿øÈ¸

#include<iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int* arr = new int[N];
	int pen=0;  //Æë±ÏÀÌ ÀÖ´Â ÀÎµ¦½º
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