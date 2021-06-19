//Quiz 1


//1-1
/*
int main() {
	for (int i = 1; i < 101; i++) {

		cout << i << '\t';
		if (i % 10 == 0) {
			cout << endl;
		}
		
	}
}
*/




//1-2
/*
int main() {
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			cout << i << "x" << j << "=" << i * j<<'\t';
		}
		cout << endl;
	}
}
*/




//1-3
/*
int main() {
	int a, b;
	cout << "두 수를 입력하라>>";
	cin >> a >> b;

	int res = a > b ? a : b;
	cout << "큰수 = " << res;
}
*/




//1-4
/*
int main() {
	double arr[5];
	double max = 0;
	cout << "5개의 실수를 입력하라";

	for (int i = 0; i < 5; i++) {
		cin >> arr[i];
		if (arr[i] > max)
			max = arr[i];
	}

	cout << "제일 큰수 = " << max;
	
}
*/



//1-5
/*
int main() {
	char s[100];
	int count = 0;
	cout << "문자들을 입력하라(100개 미만)";
	cin.getline(s, 100);
	for (int i = 0; i < 100; i++) {
		if (s[i] == 'x')
			count += 1;
	}
	cout << "x의 갯수는 " << count;
}

*/


//1-6
/*
int main() {
	string s1, s2;
	cout << "새 암호를 입력하세요>>";
	cin >> s1;
	cout << "새암호를 다시 한 번 입력하세요>>";
	cin >> s2;
	if (s1 == s2)
		cout << "같습니다" << endl;
	
}
*/




//1-7
/*
int main() {
	
	while (1) {
		char s1[100];
		cout << "종료하고싶으면 yes를 입력하세요>>";
		cin.getline(s1, 100);

		if (strcmp(s1,"yes")==0) {
			cout << "종료합니다";
			break;
		}
	}

}


*/




//1-8**
/*
int main() {
	char s[100];
	cout << "5명의 이름을 ;로 구분하여 입력하세요\n"<<">>";
	string ans;
	int max = 0;
	int n = 0;

	for (int i = 0; i < 5; i++) {
		cin.getline(s, 100, ';');
		cout << i << ':' << s;
		cout << endl;

		if (max < strlen(s)) {
			max = strlen(s);
			n = i;
			ans = s;
		}
	}
	cout << "가장 긴 이름은" << ans << endl;
}
*/


//1-9
/*
int main() {
	string name, addr;
	int age;

	cout << "이름은?";
	cin >> name;
	cout << endl;

	cout << "주소는?";
	cin >> addr;
	cout << endl;

	cout << "나이는?";
	cin >> age;
	cout << endl;

	cout << name << "," << addr << "," << age;

}



*/




//1-10

/*
#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s;
	cout << "문자열 입력>>";
	getline(cin, s);

	for (int i = 0; i < s.length(); i++)
	{
		for (int j = 0; j <= i; j++)
		{
			cout << s[j];
		}
		cout << '\n';
	}

}
*/



//1-14
/*
#include<iostream>
#include<cstring>
using namespace std;

int main() {
	int hap = 0;
	char coffee[100];
	int su;
	cout << "에스프레소 2000원, 아메리카노 2300원, 카푸치노 2500원 입니다." << endl;
	
	while (hap <= 20000) {
		int tmp = 0;
		cout << "주문>>";
		cin >> coffee >> su;

		if (strcmp(coffee, "에스프레소")==0) {
			tmp += 2000 * su;
			hap += tmp;
			cout << tmp << "원 입니다. 맛있게 드세요"<<endl;
		}

		else if (strcmp(coffee, "아메리카노") == 0) {
			tmp += 2300 * su;
			hap += tmp;
			cout << tmp << "원 입니다. 맛있게 드세요"<<endl;
		}

		else if (strcmp(coffee, "카푸치노") == 0) {
			tmp += 2500 * su;
			hap += tmp;
			cout << tmp << "원 입니다. 맛있게 드세요"<<endl;
		}

	}
	
	cout << hap << "원을 판매하여 카페를 닫습니다~";
}

*/





//1-15

#include<iostream>
#include<cstring>
using namespace std;

int main() {

	int a, c;
	char b;

	while (true) {
		cout << "?";
		cin >> a >> b >> c;
		switch (b) {
		case '+':cout << a << " " << b << " " << c << " = " << a + c << endl; break;
		case '-':cout << a << " " << b << " " << c << " = " << a - c << endl; break;
		case '*':cout << a << " " << b << " " << c << " = " << a * c << endl; break;
		case '/':cout << a << " " << b << " " << c << " = " << a / c << endl; break;
		case '%':cout << a << " " << b << " " << c << " = " << a % c << endl; break;
		default: cout << "잘못된 연산자 입니다." << endl;

		}

	}
}
