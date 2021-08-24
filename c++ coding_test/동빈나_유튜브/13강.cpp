/*
#include<iostream>
#include<algorithm>

using namespace std;

string a[20000];
int n;

bool compare(string a, string b) {
	if (a.length() < b.length()) {
		return 1;
	}
	else if (a.length() > b.length()) {
		return 0;
	}
	else {
		return a < b; // 스트링은 비교 연산자를 넣어주면 바로 사전순으로 계산해준다.
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n, compare);
	
	for (int i = 0; i < n; i++) {
		if (i > 0 && a[i] == a[i - 1]) {
			continue;
		}
		else {
			cout << a[i] << " ";
		}
	}
	return 0;
}
*/







