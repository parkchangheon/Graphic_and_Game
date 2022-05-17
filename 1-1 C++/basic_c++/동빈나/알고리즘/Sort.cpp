//#include<iostream>
//using namespace std;
//
//int main()
//{
//	int i, j, min, index, temp;
//	int array[10] = { 1,10,5,8,7,6,4,3,2,9 };
//	for (i = 0; i < 10; i++)
//	{
//		min = 9999;
//		for (j = i; j < 10; j++) {
//			if (min > array[j]) {
//				min = array[j];
//				index = j;
//			}
//		}
//
//		temp = array[i];
//		array[i] = array[index];
//		array[index] = temp;
//	}
//
//	for (i = 0; i < 10; i++){
//		cout << array[i]<<" ";
//	}
//	return 0;
//}






//#include<iostream>
//using namespace std;
//
//int main()
//{
//	int i, j, temp;
//	int array[10]= { 1,10,5,8,7,6,4,3,2,9 };
//	for (i = 0; i < 10; i++) {
//		for (j = 0; j < 9 - i; j++) {
//			if (array[j] > array[j + 1]) {
//				temp = array[j];
//				array[j] = array[j + 1];
//				array[j + 1] = temp;
//			}
//		}
//	}
//	for (i = 0; i < 10; i++) {
//		cout << array[i] << " ";
//	}
//	return 0;
//}





//#include<iostream>
//using namespace std;
//
//int main() {
//	int i, j, temp;
//	int array[10]= { 1,10,5,8,7,6,4,3,2,9 };
//	for (i = 0; i < 9; i++) {
//		j = i;
//		while (array[j] > array[j + 1]) {
//			temp = array[j];
//			array[j] = array[j + 1];
//			array[j + 1] = temp;
// 
//			j--;
//		}
//	}
//	for (i = 0; i < 10; i++) 
//		cout << array[i] << " ";
//	
//	return 0;
//}





#include<iostream>
using namespace std;

int number = 10;
int data[10]= { 1,10,5,8,7,6,4,3,2,9 };

void quickSort(int* data, int start, int end) {
	if (start >= end)
		return;

	int key = start;
	int i = start + 1;
	int j = end;
	int temp;

	while (i <= j) {

		while (data[i] <= data[key]) {
			i++;
		}

		while (data[i] <= data[key] && j > start) {
			j--;
		}
		if (i > j) {
			temp = data[j];
			data[j] = data[key];
			data[key] = temp;
		}
		else {
			temp = data[j];
			data[j] = data[i];
			data[j] = temp;
		}
	}


	quickSort(data, start, j - 1);
	quickSort(data, j + 1, end);
}

int main() {
	quickSort(data, 0, number - 1);
	for (int i = 0; i < number; i++)
		cout << data[i] << " ";
}