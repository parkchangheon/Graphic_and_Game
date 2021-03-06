// #18230번

//2*N 크기의 타일에 2*1 a개 2*2 b개 

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, a, b;
int hap = 0;
vector<int>va;
vector<int>vb;

void next(int tmp_count, int cnt, int s)
{
	if (cnt >= n)
	{
		if (s >= hap)
			hap = s;
		return;
	}

	if (tmp_count == 1) // 1일때
	{
		if (!va.empty())
		{
			s += va[va.size() - 1];
			va.pop_back();
		}
	}

	else if (tmp_count == 2) //2일때 2가지를 넣어준다.
	{
		if (va.size() >= 2) { //만약 a 벡터의 값이 2개 이상 존재할때
			if (va[va.size() - 1] + va[va.size() - 2] > vb[vb.size() - 1])
			{
				s += (va[va.size() - 1] + va[va.size() - 2]);
				va.pop_back();
				va.pop_back();
			}
			else {
				s += vb[vb.size() - 1];
				vb.pop_back();
			}
		}
		else if (vb.size() > 0) { //a 벡터의 값이 2개 이상 존재하지 않을때
			s += vb[vb.size() - 1];
			vb.pop_back();
		}
	}

	next(1, cnt + 1, s);
	next(2, cnt + 2, s);
}



int main()
{
	cin >> n >> a >> b;

	for (int i = 0; i < a; i++)
	{
		int tmp;
		cin >> tmp;
		va.push_back(tmp);
	}


	for (int i = 0; i < b; i++)
	{
		int tmp;
		cin >> tmp;
		vb.push_back(tmp);
	}

	sort(va.begin(), va.end());
	sort(vb.begin(), vb.end());

	//2*1 이랬지만, 1*2도 가능
	// DP 문제 

	next(0, 0, 0);
	cout << hap;

}


