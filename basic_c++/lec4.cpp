
/*
#include<iostream>

using namespace std;

class Circle {
	int radius;

public:
	Circle() { radius = 1; };
	Circle(int r) { radius = r; };
	double getArea();
};

double Circle::getArea() {
	return 3.14 * radius * radius;
}

int main() {
	Circle donut;
	Circle pizza(30);

	cout << donut.getArea() << endl;

	Circle* p;
	p = &donut;
	cout << p->getArea() << endl;
	cout << (*p).getArea() << endl;

	p = &pizza;
	cout << p->getArea() << endl;
	cout << (*p).getArea() << endl;
}




#include<iostream>

using namespace std;

class Circle {
	int radius;

public:
	Circle() { radius = 1; };
	Circle(int r) { radius = r; };
	void setRadius(int r) { radius = r; }
	double getArea();
};

double Circle::getArea() {
	return 3.14 * radius * radius;
}

int main() {

	Circle circleArr[3];

	circleArr[0].setRadius(10);
	circleArr[1].setRadius(20);
	circleArr[2].setRadius(30);

	for (int i = 0; i < 3; i++) {
		cout << "Circle " << i << "의 면적은 " << circleArr[i].getArea() << endl;


	Circle* p;
	p = circleArr;
	for (int i = 0; i < 3; i++) {
		cout << p->getArea() << "는" <<"반지름"<< endl;
		p++;
		}
	}

}




#include<iostream>

using namespace std;

class Circle {
	int radius;

public:
	Circle() { radius = 1; };
	Circle(int r) { radius = r; };
	void setRadius(int r) { radius = r; }
	double getArea();
};

double Circle::getArea() {
	return 3.14 * radius * radius;
}



int main() {
	Circle circle[2][3];

	circle[0][0].setRadius(1);
	circle[0][1].setRadius(2);
	circle[0][2].setRadius(3);
	circle[1][0].setRadius(4);
	circle[1][1].setRadius(5);
	circle[1][2].setRadius(6);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			cout << circle[i][j].getArea() << endl;
		}
	}
	return 0;
}



//동적 메모리 할당 및 반환




#include<iostream>
using namespace std;

int main() {
	int* p = new int;

	if (!p) {
		cout << "메모리 할당할 수 없습니다.";
		return 0;
	}

	*p = 5;
	int n = *p;
	cout << "*p = " << *p << '\n';
	cout << " n = " << n << '\n';

	delete p;

}




#include <iostream>
using namespace std;

int main() {
	cout << "입력할 정수의 개수는?";
	int n;
	cin >> n;
	if (n <= 0) return 0;
	int* p = new int[n];
	if (!p) {
		cout << "메모리를 할당할 수 없습니다.";
		return 0;
	}

	for (int i = 0; i < n; i++) {
		cout << i + 1 << "번째 정수 : ";
		cin >> p[i];
	}

	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += p[i];
	cout << "평균 = " << sum / n << endl;

	delete[] p;
}



#include<iostream>
using namespace std;

class Circle {
	int radius;

public:
	Circle() { radius = 1; };
	Circle(int r) { radius = r; };
	~Circle();
	void setRadius(int r) { radius = r; }
	double getArea();
};

double Circle::getArea() {
	return 3.14 * radius * radius;
}

Circle::~Circle() {
	cout << "소멸자 실행";
}

int main() {
	Circle* p, * q;

	p = new Circle;
	q = new Circle(30);

	cout << p->getArea() << endl<< q->getArea() << endl;
	delete p;
	delete q;
}




#include <iostream>
using namespace std;

class Circle {
	int radius;
public:
	Circle();
	~Circle() { }
	void setRadius(int r) { radius = r; }
	double getArea() { return 3.14 * radius * radius; }
};

Circle::Circle() {
	radius = 1;
}



int main() {
	cout << "생성하고자 하는 원의 개수?";
	int n, radius;
	cin >> n; // 원의 개수 입력

	Circle* pArray = new Circle[n]; // n 개의 Circle 배열 생성
	for (int i = 0; i < n; i++) {
		cout << "원" << i + 1 << ": "; // 프롬프트 출력
		cin >> radius; // 반지름 입력
		pArray[i].setRadius(radius); // 각 Circle 객체를 반지름으로 초기화
	}

	int count = 0; // 카운트 변수
	Circle* p = pArray;
	for (int i = 0; i < n; i++) {
		cout << p->getArea() << ' '; // 원의 면적 출력
		if (p->getArea() >= 100 && p->getArea() <= 200)
			count++;
		p++;
	}
	cout << endl << "면적이 100에서 200 사이인 원의 개수는 "
		<< count << endl;

	delete[] pArray; // 객체 배열 소멸
}

*/



/*
class Circle {
	int radius;
public:
	Circle() { this->radius = 1; }
	Circle(int radius) { this->radius = radius; }
	void setRadius(int radius) { this->radius = radius; }
};
*/





/*
#include<iostream>

using namespace std;

int main() {
	string str;
	string address("서울시 성북구 삼선동 389");
	string copyAddress(address); // copyAddress로 address를 복사한다.

	cout << copyAddress;


	char text[] = { 'l','o','v','\0' };
	string title(text);
}







#include<iostream>

using namespace std;

int main() {
	string* p = new string("C++");

	cout << *p;
	p->append(" Great!!");
	cout << *p;

	delete p;
}
*/




/*
#include<iostream>
#include<string>

using namespace std;

int main() {
	string names[5];

	for (int i = 0; i < 5; i++) {
		cout << "이름 >> ";
		getline(cin, names[i], '\n');
	}

	string latter = names[0];
	for (int i = 1; i < 5; i++){
		if (latter < names[i])
			latter = names[i];
	}
	cout << "사전상 가장 뒤에 나오는 문자열은 " << latter << endl;
}
*/



/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;

	cout << "문자열을 입력하세요(한글 안됨) " << endl;
	getline(cin, s, '\n'); // 문자열 입력
	int len = s.length(); // 문자열의 길이

	for (int i = 0; i < len; i++) {
		string first = s.substr(0, 1); // 맨 앞의 문자 1개를 문자열로 분리
		string sub = s.substr(1, len - 1); // 나머지 문자들을 문자열로 분리
		s = sub + first; // 두 문자열을 연결하여 새로운 문자열로 만듦
		cout << s << endl;
	}
}


#include<iostream>
#include<string>
using namespace std;

int main() {
	string a("Hello C++");
	cout << a.length() << endl;
	a.append("!!");
	cout << a << endl;
	cout << a.at(6) << endl;
	cout << a.find("C") << endl;
	int n = a.find("+++");
	cout << n << endl;
	a.erase(1, 3);
	cout << a << endl;
}



*/