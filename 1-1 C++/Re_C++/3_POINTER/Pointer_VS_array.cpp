#include<iostream>
using namespace std;

void Test(char a[])
{
	a[2] = 'A';
}

void ChooseLottery(int numbers[])
{
	srand(unsigned(time(0))); //random seeds

	int count = 0;
	while (count != 6)
	{
		int randValue = 1 + (rand() % 45);
		bool found = false;

		for(int i=0; i< count;i++)
		{ 
			//이미 찾은 값
			if (numbers[i] == randValue)
			{
				found = true;
				break;
			}
		}

		if (found == false)
		{
			numbers[count] = randValue;
			count++;
		}
	}
	
}


int main()
{
	char msg[] = { 'h','e','l','\0' };
	cout << msg << endl;

	const char* test1 = "Hello World";
	char test2[] = "Hello World";
	test2[0] = 'R';


	//포인터는 주소를 담는 바구니이지만,
	//배열은 그 자체로 데이터가 붙어있는 개념이다.
	// 하지만 배열은 시작 주소를 나타내고 있다.


	//배열을 어떤 함수의 인자로 넘기게 된다면?
	Test(test2);

	cout << test2 << endl;
	
	return 0;
}