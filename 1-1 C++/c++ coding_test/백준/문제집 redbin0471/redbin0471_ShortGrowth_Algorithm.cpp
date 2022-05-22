//12865¹ø

#include<iostream>
#include<vector>
using namespace std;


vector <vector<int>> vec;
int n, w, v, k; //°¹¼ö, ¹«°Ô, °¡Ä¡, ÃÖ´ë ¹«°Ô
int maximum=0;

void Group(int count, int w_hap, int v_hap) {
	if (count > n)
		return;

	else if (w_hap <= k) {
		//µ¡¼ÀÃ³¸® ¾ÈÇØÁÜ (Æ÷ÇÔ ¾ÈÇÔ)
		Group(count + 1, w_hap, v_hap);

		//µ¡¼ÀÃ³¸® ÇØÁÜ (Æ÷ÇÔÇÑ´Ù)
		w_hap += vec[count][0];
		v_hap += vec[count][1];
		Group(count + 1, w_hap, v_hap);

		if (v_hap > maximum)
			maximum = v_hap;
	}
}

int main()
{
	cin >> n >> k;
	
	for (int i = 0; i < n; i++) {
		cin >> w>> v;
		vec.push_back({ w, v });
	}

	Group(0, 0, 0);
	cout << maximum;
}

 