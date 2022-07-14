//스트링 클래스를 활용한 문자열 사용

//string 사용하는 방법은 2가지 방법이 있다.
//c-string 과 string 클래스이다.

//1) string 클래스 
//#include<iostream>
//#include<string>
//using namespace std;
//
////2) c-string은 초기에 할당받은 메모리 크기 이상의 문자열을 저장할 수 없어, 프로그램 작성에 어려움이 있다
//int main()
//{
//	string str = "I Love ";
//	str.append("C++");
//
//	string* p = new string("win");
//	cout << *p;
//
//	p->append(" the game?");
//	cout << *p;
//	delete p;
//
//}



//#include<iostream>
//#include<string>
//using namespace std;
//
//int main()
//{
//	//string 방식
//	string str;
//	string address("서울시 ");
//	string copyadd(address);
//
//	//c-string
//	char text[] = { 'L','O','V','E' };
//	string title(text);
//
//	cout << str << endl;
//	cout << address << endl;
//	//....
//}



//#include<iostream>
//#include<string>
//using namespace std;
//
//int main()
//{
//	string name[5];
//
//	for (int i = 0; i < 5; i++) {
//		cout << "이름 >> ";
//		getline(cin, name[i], '\n');
//	}
//
//	string latter = name[0];
//	for (int i = 1; i < 5; i++)
//	{
//		if (latter < name[i])
//			latter = name[i];
//	}
//
//}




#include<iostream>
#include<string>
using namespace std;

//int main() {
//	string s;
//
//	cout << "아래 문자열 입력" << endl;
//	getline(cin, s, '\n');
//	int len = s.length();
//
//	for (int i = 0; i < len; i++)
//	{
//		string first = s.substr(0, 1);
//		string sub = s.substr(1, len - 1);
//		s = sub + first;
//		cout << s << endl;
//	}
//}


//int main()
//{
//	string s;
//	cout << "입력 : " << endl;
//	getline(cin, s, '\n');
//
//	int sum = 0;
//	int startindex = 0;
//
//	while (true) {
//		int findex = s.find('+', startindex);
//		if (findex == -1)
//		{
//			string part = s.substr(startindex);
//			if(part == "")break;
//			cout << part << endl;
//			sum += stoi(part);
//			break;
//		}
//		int count = findex - startindex;
//		string part = s.substr(startindex, count);
//	}
//}