#include<iostream>
using namespace std;

#include"calc.h"
#include"add.h"

void calculator::run() {
	cout << "두개의 수를 입력하시오";
	int a, b;
	cin >> a >> b;
	add add(a, b);
	cout << "결과는 : " << add.process();
}