
//#include<iostream>
//using namespace std;
//
//int main() {
//	//===================포인터 예제
//	//short sArr[10] = { 1,2,3,4,5,6,7,8,9,10 }; // short배열.
//	//int* pI = (int*)sArr; //강제 캐스팅해서 int 포인터로 받음.
//	//int iData = *((short*)(pI + 2));
//	//printf("1번 문제 정답 : %d \n", iData);
//
//	//char cArr[2] = { 1,1 };
//	//short* pS = (short*)cArr;
//	//iData = *pS;
//
//	//printf("2번 문제 정답 : %d\n", iData);
//	//return 0;
//
//
//	//=============================
//
//	const int cint = 100;
//	// 상수화 시켰다. 변경 불가
//
//	int a = 0;
//	int* pInt = &a;
//
//	*pInt = 1;
//	pInt = nullptr;
//
//	int b = 0;
//	const int* pConstInt = &a;
//	// 가리키고 있는 원본 변수를 상수화한거다
//	//*pConstInt =100;이 불가능하다.
//	pConstInt = &b; // 하지만 다른것을 가리키는건 가능
//
//
//	int* const pIntConst = &a; 
//	// 포인터가 가리키고 있는 주소를 상수화
//	*pIntConst = 400;
//	//pIntConst = &b; 
//
//}



//10-16
//#include<iostream>
//#include<vector>
//using namespace std;
//
//
//class Shape {
//protected:
//	virtual void draw() = 0;
//public:
//	void paint() {
//		draw();
//	}
//};
//
//class Circle :public Shape {
//protected:
//	virtual void draw() { cout << "Cirlce" << endl; }
//};
//
//
//class Rect :public Shape {
//protected:
//	virtual void draw() { cout << "Rectangle" << endl; }
//};
//
//
//class Line :public Shape {
//protected:
//	virtual void draw() { cout << "Line" << endl; }
//};
//
//
//
//
//int main() {
//	int selector;
//
//	vector<Shape*> v;
//	vector<Shape*>::iterator it;
//
//	cout << "그래픽 에디터입니다." << endl;
//	while (true) {
//		cout << "삽입 :1, 삭제:2, 모두보기:3, 종료:4 >>";
//		cin >> selector;
//		switch (selector) {
//		case 1: {
//			int n;
//			cout << "선:1, 원:2, 사각형:3 >> ";
//			cin >> n;
//
//
//			switch (n) {
//			case 1:
//				v.push_back(new Line());
//				break;
//
//			case 2:
//				v.push_back(new Circle());
//				break;
//
//			case 3:
//				v.push_back(new Rect());
//				break;
//
//			default:
//				cout << "잘못된 선택입니다." << endl;
//				break;
//			}
//			break;
//		}
//
//		case 2: {
//			int n;
//			cout << "삭제하고자 하는 도형 인덱스 >>";
//			cin >> n;
//			if (n > v.size() || n < 0) { // 예외처리
//				cout << "인덱스 입력 오류" << endl;
//				break;
//			}
//			it = v.begin();
//			v.erase(it + n);
//			break;
//		}
//
//
//		case 3: {
//			int i = 0;
//			for (it = v.begin(); it != v.end(); it++, i++) {
//				cout << i << ": ";
//				v.at(i)->paint();
//			}
//			break;
//		}
//		case 4:
//			return 0;
//
//		default:
//			cout << "잘못된 명령입니다." << endl;
//			break;
//
//		}
//	}
//}




#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int myints[] = { 10,20,30,40 };
	int* p;

	p = find(myints, myints + 4, 30);
	if (p != myints + 4)
		cout << "내가 찾고자 하는 값은 " << *p << " 이다" << endl;
	else
		cout << "내가 찾고자 하는 값이 없다." << endl;

	vector<int> v(myints, myints + 4);
	vector<int>::iterator it;

	it = find(v.begin(), v.end(), 50);
	if (it != v.end())
		cout << "내가 찾고자 하는 값은 " << *it << endl;
	else
		cout << "내가 찾고자 하는 값이 없다" << endl;
	return 0;
}

// find(start,end) 는 start~end 사이 선형 검색을 수행한다.
// 위의 find는 start~end 사이에서 30값을 탐색한다
// 만약 찾는 값이 없다면 조건문에서 0을 반환한다.


//#include<iostream>
//#include<algorithm>
//#include<vector>
//
//using namespace std;
//
//int main() {
//	vector<int>v = { 1,2,3,4,5,6,7,8,9 };
//
//	for (auto& n : v) {
//		cout << n << ",";
//	}
//	cout << endl;
//
//	reverse(v.begin(), v.end());
//
//	for (auto& n : v)
//	{
//		cout << n << ",";
//	}
//	cout << endl;
//	
//
//}




//#include<iostream>
//#include<algorithm>
//#include<vector>
//
//using namespace std;
//
//int main() {
//	vector<int>v = { 1,4,2,6,8,3,5,7,9 };
//
//	for (auto& n : v) {
//		cout << n << ",";
//	}
//	cout << endl;
//
//	sort(v.begin(), v.end());
//
//	for (auto& n : v)
//	{
//		cout << n << ",";
//	}
//	cout << endl;
//
//
//}



//#include<iostream>
//#include<algorithm>
//#include<vector>
//#include<string>
//
//using namespace std;
//
//int main() {
//	vector<int> v;
//	v.push_back(3);
//	v.push_back(1);
//	v.push_back(1);
//	v.push_back(2);
//	v.push_back(3);
//	v.push_back(3);
//	v.push_back(4);
//	v.push_back(3);
//
//	size_t n = count(v.begin(), v.end(), 3);
//	cout << n;
//
//}



//#include<iostream>
//#include<algorithm>
//#include<vector>
//using namespace std;
//
//int main() {
//	vector<int>v = { 1,2,3,4,5,6,7,8,9 };
//	vector<int>w = { 0,0,1,1,1,1,1 };
//	
//
//	copy(v.begin()+2,v.begin()+5,w.begin());
//
//	for (int i = 0; i < (int)w.size(); i++)
//		printf("%d ", w[i]);
//}
