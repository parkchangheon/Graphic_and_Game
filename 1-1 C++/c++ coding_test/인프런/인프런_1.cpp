// 재귀함수와 스택

/*
#include<iostream>
using namespace std;


void DFS(int x) {
	if (x > 0) {
		cout << x << ' ';
		DFS(x - 1);
	}
}

int main() {
	DFS(3);
}

*/



//재귀함수 2진수
/*
#include<iostream>
using namespace std;


void DFS(int x) {
	if (x== 0) 
		return;
	else {
		DFS(x / 2);
		cout << x % 2;
	}
}

int main() {
	int n;
	cin >> n;
	DFS(n);
}
*/




//부분집합 구하기

/*
#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> v;

void DFS(int x, vector<int> tmp) {
	if (x == 4) {
		if (tmp.size() > 0) {
			for (int i = 0; i < tmp.size(); i++) {
				cout << tmp[i];
			}
		}
		cout << endl;
	}

	if (x <= 3) {
		DFS(x + 1, tmp);
		tmp.push_back(x);
		DFS(x + 1,tmp);
	}
}

int main() {
	vector<int> tmp;
	DFS(1,tmp);

}
*/




//#include <stdio.h>
//
//int data[] = { 1,2,3,4 };
//int flag[] = { 0,0,0,0 };
//
//void powerset(int n, int depth)
//{
//	if (n == depth) {
//		int i;
//		printf("{");
//		for (i = 0; i < n; i++) {
//			if (flag[i] == 1)printf("%d ", data[i]);
//		}
//		printf("}\n");
//		return;
//	}
//	flag[depth] = 1;
//	powerset(n, depth + 1);
//	flag[depth] = 0;
//	powerset(n, depth + 1);
//}
//
//int main()
//{
//	powerset(sizeof(data) / sizeof(int), 0);
//	return 0;
//}






// 합이 같은 부분집합 구하기
/*
#include<iostream>
using namespace std;
int* check;
int n;
int total;
bool FT = false;

void DFS(int L, int sum) {
	if (L == n+1) {
		if (sum == total - sum) {
			FT = true;
			cout << "같습니다" << endl;
		}
		return;
		
	}

	else {
		DFS(L + 1, sum);
		if (FT == true) return;
		sum+=check[L];
		DFS(L + 1, sum);
		if (FT == true) return;
	}
}

int main() {
	cout << "n을 입력하세요 : ";
	cin >> n;
	check = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> check[i];
	}

	for (int i = 0; i < n; i++) {
		total += check[i];
	}

	DFS(0, 0);

	if (FT == false)
		cout << "없습니다.";

}
*/




/*

#include<iostream>
using namespace std;

int m, n;
int* res;

void DFS(int l) {
	if (l == m) {
		for (int i = 0; i < m; i++) {
			cout << res[i];
		}
		cout << endl;
	}

	else {
		for (int i = 1; i <= n; i++) {
			res[l] = i;
			DFS(l+1);
		}
	}

}

int main() {
	cin >> n >> m;
	res = new int[m] {};
	DFS(0);
}

*/



