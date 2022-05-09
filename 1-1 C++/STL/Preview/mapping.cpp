#include<iostream>
#include <map>

using namespace std;

int main()
{
	map<string, int> mp = {
		{"key1",10},
		{"key12", 20},
		{"key14",33}
	};

	cout << mp["key1"] << endl;
	pair<string, int> pp;
	pp = { "new",99 };
	mp.insert(pp);
	cout << mp["new"] << endl;
}