#include<iostream>
#include<string>
using namespace std;


class Circle {
    int radius;
    string name;

public:
    void setCircle(string name, int radius) { this->name = name; this->radius = radius; };
    double getArea();
    string getName() { return name; };
};


class CircleManager {
    Circle* p; 
    int size;
    int r;
    string s;
public:
    CircleManager(int size);
    ~CircleManager();
    void searchByName();
    void searchByArea(); 
};



double Circle::getArea() {
    return radius * radius * 3.14;
}

CircleManager::CircleManager(int size) {
    p = new Circle[size];
    this->size = size;
    for (int i = 0; i < size; i++) {
        cout << "원 " << i + 1 << " 의 이름과 반지름 >>";
        cin >> s >> r;
        p[i].setCircle(s, r);
    }
}

CircleManager::~CircleManager() {
    delete[]p;
}
void CircleManager::searchByName() {
    cout << "검색하고자 하는 원의 이름>>";
    cin >> s;
    for (int i = 0; i < size; i++) {
        if (s == p[i].getName()) {
            cout << s << "의 면적은 " << p[i].getArea() << endl;
        }
    }
}
void CircleManager::searchByArea() {
    cout << "최소 면적을 정수로 입력하세요>>";
    cin >> r;
    for (int i = 0; i < size; i++) {
        if (r < p[i].getArea()) {
            cout << p[i].getName() << "의 면적은 " << p[i].getArea() << ",";
        }
    }
}




int main() {
    int size;
    cout << "원의 개수 >> ";
    cin >> size;
    CircleManager C(size);
    C.searchByName();
    C.searchByArea();
    


}