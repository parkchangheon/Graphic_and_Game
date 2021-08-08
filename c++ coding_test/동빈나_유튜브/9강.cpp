// c++ STL sort 사용해보기 


/*
#include<iostream>
#include<algorithm>

using namespace std;

int main() {
	int a[10] = { 9,3,1,2,4,5,1,2,5,7 };
	sort(a, a + 10); //메모리의 주소를 통해 정렬이 가능. 첫주소인 9, 마지막 주소인 7
	for (int i = 0; i < 10; i++)
		cout << a[i]<<' ';
}

*/



// 정렬 기준을 직접 정해보기

/*
#include<iostream>
#include<algorithm>

using namespace std;

bool compare(int a, int b) {
	//return a < b; // 오름차순 구현
	return a > b;   // 내림차순 구현
}

int main() {
	int a[10] = { 9,3,1,2,4,5,1,2,5,7 };
	sort(a, a + 10,compare);
	for (int i = 0; i < 10; i++)
		cout << a[i] << ' ';
}
*/




//데이터를 묶어서 정렬하는 방법
/*
#include<iostream>
#include<algorithm>

using namespace std;

class Student {
public:
	string name;
	int score;
	Student(string name, int score) {
		this->name = name;
		this->score = score;
	}

	//정렬 기준은 점수가 작은 순서
	bool operator<(Student& student) {
		return this->score < student.score;//내 점수가 낮다면 우선순위가 높다. (작은것부터 출력)
	}
};

int main() {
	Student students[] = {
		Student("Na",90),
		Student("KIM",100),
		Student("Lee",55)
	};
	sort(students, students + 3);

	for (int i = 0; i < 3; i++) {
		cout << students[i].name<<' ';
	}
}
*/


