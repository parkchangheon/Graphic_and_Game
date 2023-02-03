#include<iostream>
using namespace std;

int main()
{
	int a[10] = { 1,2,3 };

	int apartment[2][5] = { {1,2,3,4,5},{1,2,3,4,5} };

	for (int floor = 0; floor < 2; floor++)
	{
		for (int room = 0; room < 5; room++)
		{
			int num = apartment[floor][room];
			cout << num << " ";
		}
		cout << endl;
	}

	




	//사용 예시 (로그라이크에서 맵 만들때)

	int map[5][5] =
	{
		{1,1,1,1,1},
		{1,0,0,1,1},
		{0,0,0,0,1},
		{1,0,0,0,0},
		{1,1,1,1,1}
	};

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			int info = map[y][x];
			cout << info;
		}
		cout << endl;
	}

	return 0;

}