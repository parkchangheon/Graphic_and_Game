

//#include <iostream>
//
//using namespace std;
//
//class Circle {
//	int radius;
//
//public:
//	Circle() { this->radius = 1; }
//	Circle(int r) { this->radius = r; }
//	void setRadius(int r) { this->radius = r; }

	//this 는 객체 자신에 대한 포인터로서 클래스의 멤버함수 안에서만 사용이 된다.
	//this는 객체에 대한 주소라고 생각하면 된다. (자신을 가리키는 포인터)
	//this는 멤버 함수에서만 사용할 수 있다.==>해당 함수들은 어떤 객체에도 포함되지 않기 때문
	//정적 멤버함수는 this를 사용할 수 없다.

	/*void setRadius(Circle* this, int x)
	{
		this->radius = x;
	}*/
	//사실은 이런 식 (컴파일러가 이와 같이 변환 시킨다.)
	//Circle ob;
	//ob.setRadius(5);  ==> ob.setRadius(&ob,5); 라고 생각하면 됨
//};

//int main()
//{
//	
//}




// # STRING

//#include<iostream>
//#include<string>
//using namespace std;
//
//int main()
//{
//	// 스트링 객체 생성 방법
//	string str;
//	string address("서울시 양천구 목동");
//	string copyAddress(address); //address를 복사한것. 변수 coptAddress에 넣어줌
//
//	//c-string 방식
//	char text[] = { 'L','o','v','e',' ','C','+','+','\0' };
//	string title(text);
//
//
//	//동적 생성
//	string* s = new string("C++");
//	cout << *s;
//	s->append(" what is this!");
//	cout << *s;
//	delete s;
//}



//#include<iostream>
//#include<string>
//
//using namespace std;
//
//int main() {
//	string str;
//	cin >> str; //이것은 공백 전까지 입력이 가능
//	cout << str << endl;
//
//	//이것을 해결하는 방법이 getline()
//
//	string name;
//	getline(cin, name, '\n'); //'\n'을 만날때까지 입력하라.(엔터)
//
//}




//#include<iostream>
//#include<string>
//
//using namespace std;
//
//int main()
//{
//	string names[5];
//	for (int i = 0; i < 5; i++)
//	{
//		cout << "이름 >> ";
//		getline(cin, names[i], '\n');
//	}
//
//	string latter = names[0];
//	for (int i = 1; i < 5; i++) {
//		if (latter < names[i]) {
//			latter = names[i];
//		}
//	}
//
//	cout << "사전에서 가장 뒤에 나오는 문자열은" << latter << endl;
//}



//#include<iostream>
//#include<string>
//#include<locale>
//using namespace std;
//
//int main()
//{
//	string name = "Kitae";
//	string alis = "Kito";

	//compare
	/*int res = name.compare(alis);
	if (res == 0)
		cout << "두 문자열이 같다.";
	else if (res < 0)
		cout << name << "이 " << alis << "보다 앞에 온다.";
	else
		cout << alis << "가 " << name << "보다 앞에 온다";*/

	//+, =, +=
	// 문자열 삽입
	/*string a = "I love c++";
	a.insert(2, "really ");
	cout << a;*/

	//문자열 대체 
	/*string a("i Did This");
	a.replace(2, 9, "love");
	cout << a;*/

	//string a = "I study c++";
	//int length = a.length();
	//int size = a.size();

	//a.erase(0, 7);
	//a.clear();

	//서브 스트링(특정 구간을 잘라 내는 것)
	//string b = "i love this";
	//string c = b.substr(2, 4);
	//string d = b.substr(2);
	//cout << b << " " << c << " " << d;

	//문자열 검색
	//int index = a.find("study"); //인덱스 2를 리턴
	//발견할 수 없으면 -1을 리턴한다.
	//index = a.find('c', 7); // 인덱스 7부터 c를 찾는다.
	

	//at 함수  --> 특정 문자를 리턴한다. [] 인덱스와 같음
	//char ch1 = a.at(8);
	//char ch2 = a[8];
	//cout << ch1 << ch2;

	//문자열의 숫자 변환
//	string year = "2014";
//	int n = stoi(year);
//	cout << n;
//
//	a = "hello";
//	for (int i = 0; i < a.length(); i++)
//	{
//		a[i] = toupper(a[i]);
//		cout << a;
//
//		if (isdigit(a[0]))
//			cout << "숫자";
//		else if(isalpha(a.at(0)))
//			cout<<"문자";
//	}
//}



//#include<iostream>
//#include<string>
//
//using namespace std;
//
//int main()
//{
//	string a = "I love you";
//	
//	for (int i = 0; i < a.length(); i++)
//	{
//		string first = a.substr(0, 1);
//		string sub = a.substr(1);
//		a = sub + first;
//		cout << a << endl;
//		
//	}
//}






//#include<iostream>
//#include<string>
//
//using namespace std;
//
//int main()
//{
//	string s;
//	getline(cin, s, '\n');
//
//	int sum = 0;
//	int start_index = 0;
//
//	while (true) {
//		int findex = s.find('+', start_index);
//		if (findex == -1) //+없을때,
//		{
//			string part = s.substr(start_index);
//			if (part == "")
//				break; //2+3+ 인경우
//			cout << part<<endl;
//			sum += stoi(part);  // 2+3 인 케이스
//			break;
//		}
//		int count = findex - start_index;
//		string part = s.substr(start_index, count);
//
//		cout << part << endl;
//		sum += stoi(part);
//		start_index = findex + 1;
//	}
//	cout << "숫자들의 합은 " << sum<< endl;
//}



//#include<iostream>
//#include<string>
//
//using namespace std;
//
//int main()
//{
//	string s;
//	cout << " 여러줄의 문자열을 입력하세요 입력끝값은 & 문자입니다." << endl;
//	getline(cin, s, '&');
//	cin.ignore(); // 뒤에 입력되는 엔터 값을 무시하기 위함
//
//	string f, r;
//	cout << endl << "find";
//	getline(cin, f, '\n');
//	cout << "replace";
//	getline(cin, r, '\n');
//
//	int startindex = 0;
//	while (true) {
//		int findex = s.find(f, startindex);
//		if (findex == -1)
//			break;
//		s.replace(findex, f.length(), r); // findex부터 문자열 f만큼 r로 바꿔줌
//		startindex = findex + r.length();
//	}
//	cout << s << endl;
//}