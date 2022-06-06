// #18230번

//2*N 크기의 타일에 2*1 a개 2*2 b개 

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, a, b;
int hap=0;
int cnt = 0;
vector<int>va;
vector<int>vb;

void next(int tmp_count, int s)
{
	if (cnt > n)
	{
		if (s >= hap)
			hap = s;
		return; 
	}

	if (tmp_count == 1) // 1일때
	{
		if (!va.empty())
		{
			s += va[va.size()-1];
			va.pop_back();
		}
		cnt += 1;
	}

	else if (tmp_count == 2) //2가지 경우가 가능
	{
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
		cnt += 2;
	}
	for (int i = 0; i < va.size(); i++)
		cout << va[i] << ' ';
	cout << endl;
	for (int i = 0; i < vb.size(); i++)
		cout << vb[i] << ' ';
	cout << endl;


	next(1, s);
	next(2, s);
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

	next(0, 0);
	cout<<hap;
	
}