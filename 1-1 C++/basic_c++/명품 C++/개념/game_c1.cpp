
/*
double area(int r);
double area(int r) {
	return 3.14 * r*r;
}


int main() {
	std::cout << "Hello \n";
	int r = 4;
	double res = area(r);
	cout << res << endl;

	int h, w;
	cout << "h와 w 입력하세요" << endl;
	cin >> h >> w;
	cout << h << ' '<<w;
	return 0;
}
*/


/*
int main() {
	char name1[6] = { 'G','r','a','c','e','\0' }; //cstring 방법으로, 널문자(\0)로 끝나는 char 배열을 나타냄. 이것은 name1 문자열
	char name2[5] = { 'G','r','a','c','e' }; //문자열이 아니라, 단순 문자 배열이다.

	char name3[6] = "Grace";
	char name4[] = "Grace"; //배열크기가 자동으로 6으로 저장됨.

}





int main() {

	char name[6];
	cin >> name;
	cout << name;
}
*/



//비밀번호 정상 입력하기
/*
#include<iostream>
#include<cstring>
using namespace std;


int main() {
	char pw[]="thisispw";
	char input_pw[10];
	while (true) {
		cout << "비밀번호를 입력하세요 : ";
		cin >> input_pw;
		if (strcmp(input_pw, pw) == 0) {
			cout << "프로그램을 정상 종료합니다" << endl;
			break;
		}
		else {
			cout << "암호 오류" << endl;
		}
	}
}
*/




//하지만의 위의 방법은 공백을 받을 수 없다.
//그러므로, cin.getline을 이용

/*
#include<iostream>
#include<cstring>
using namespace std;


int main() {
	char addr[100];
	cin.getline(addr, 100);  //cin.getline(addr, 100,'\n');과 동일. 마지막은 문자열 입력 끝을 지정하는 구분 문자이다.
	cout << addr;
	
}
*/



//현재까지 방법은 cstring을 이용한 방법이다. 
// 하지만, 이는 크기에 의해 문자열의 크기가 고정되는 단점을 가지고 있으나,
//string클래스는 문장열의 크기에 제약이 없기 때문이다.

/*
#include<iostream>
#include<string>
using namespace std;

int main() {
	string song("Falling love with you");
	string elvis("Elvis");

	string singer;
	cout << song + " 을 부른 가수의 이름은? ";
	cout << " (첫글자는"<<elvis[0] << ")  : " ;
	getline(cin, singer);
	if (singer == elvis) {
		cout << "맞았습니다";
	}
	else {
		cout << "틀렸습니다." + elvis + "입니다" << endl;
	}

}

*/



/*
#include<iostream>
#include<string>

using namespace std;

int main() {
	string romio;
	string juliet;


	while (true) {
		cout << "로미오>>";
		cin >> romio;
		cout<< "줄리엣>>";
		cin >> juliet;


		if (romio == "바위") {
			if (juliet == "가위") {
				cout << "로미오가 이겼습니다"<<endl;
			}
			else if (juliet == "보") {
				cout << "줄리엣이 이겼습니다"<<endl;
			}
			else {
				cout << "비겼습니다" << endl;
				break;
			}
		}



		if (romio == "보") {
			if (juliet == "가위") {
				cout << "줄리엣이 이겼습니다" << endl;
			}
			else if (juliet == "바위") {
				cout << "로미오가 이겼습니다" << endl;
			}
			else {
				cout << "비겼습니다" << endl;
				break;
			}
		}




		if (romio == "가위") {
			if (juliet == "바위") {
				cout << "줄리엣이 이겼습니다" << endl;
			}
			else if (juliet == "보") {
				cout << "로미오가 이겼습니다" << endl;
			}
			else {
				cout << "비겼습니다" << endl;
				break;
			}
		}

	}


}




#include<iostream>
using namespace std;

int main() {
	for (int n = 0; n < 4; n++) {
		for (int m = 0; m < n + 1; m++) {
			cout << "*";
		}
		cout << endl;
	}
}
*/

