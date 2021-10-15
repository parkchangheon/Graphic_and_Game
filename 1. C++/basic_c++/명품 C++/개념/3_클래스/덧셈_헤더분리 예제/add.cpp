#include<iostream>

using namespace std;

#include "add.h"

add::add(int x, int y) {
	a = x;
	b = y;
}

int add::process() {
	return a + b;
}