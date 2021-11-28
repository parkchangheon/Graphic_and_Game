#include<iostream>
#include<vector>
using namespace std;

class Shape {
protected:
	virtual void draw() = 0;
public:
	void paint() {
		draw();
	}
};

class Circle :public Shape {
protected:
	virtual void draw() { cout << "Cirlce" << endl; }
};


class Rect :public Shape {
protected:
	virtual void draw() { cout << "Rectangle" << endl; }
};


class Line :public Shape {
protected:
	virtual void draw() { cout << "Line" << endl; }
};




int main() {
	int selector;
	vector<Shape *> v;
	vector<Shape*>::iterator it;

	cout << "그래픽 에디터입니다."<<endl;
	while (true) {
		cout << "삽입 :1, 삭제:2, 모두보기:3, 종료:4 >>";
		cin >> selector;
		switch (selector) {
		case 1: {
			int n;
			cout << "선:1, 원:2, 사각형:3 >> ";
			cin >> n;
			switch (n) {
			case 1:
				v.push_back(new Line());
				break;

			case 2:
				v.push_back(new Circle());
				break;

			case 3:
				v.push_back(new Rect());
				break;

			default:
				cout << "잘못된 선택입니다." << endl;
				break;
			}
			break;
		}

		case 2: {
			int n;
			cout << "삭제하고자 하는 도형 인덱스 >>";
			cin >> n;
			if (n > v.size() || n < 0) { // 예외처리
				cout << "인덱스 입력 오류" << endl;
				break;
			}
			it = v.begin();
			v.erase(it + n);
			break;
		}
		case 3: {
			int i = 0;
			for (it = v.begin(); it != v.end(); it++, i++) {
				cout << i << ": ";
				v.at(i)->paint();
			}
			break;
		}
		case 4:
			return 0;

		default:
			cout << "잘못된 명령입니다." << endl;
			break;

		}
	}
}