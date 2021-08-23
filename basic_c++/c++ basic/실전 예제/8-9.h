#include<iostream>
using namespace std;

string seat_arr[3][8] = {
{"---","---", "---", "---", "---", "---", "---" },
{"---","---", "---", "---", "---", "---", "---" },
{"---","---", "---", "---", "---", "---", "---" },
};



class reservation {

public:
	reservation() { ; };
};

class seat {

public:
	seat() { ; }

	void set_seat(int plane, int seat, string name) {
		seat_arr[plane][seat] = name;
	}

	void plane_seat(int number) {
		for (int i = 0; i < 8; i++) {
			cout << seat_arr[number - 1][i] << " ";
		}
		cout << endl;
	}

	void seat_show() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 8; j++) {
				cout << seat_arr[i][j] << " ";
			}
			cout << endl;
		}

	}
};



