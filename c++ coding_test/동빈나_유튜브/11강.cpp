// 힙 정렬



//힙구조는 완전 이진 트리 형식을 따른다
//이떄 하나의 노드는 logn을 따른다. 
//그런데 여기서, 힙을 만들기 위해서는 n/2 만 해줘도 힙 구조를 만들 수 있다.
//그러므로 실제 시간 복잡도는 n/2 * log n 으로 표현할 수 있는데 
//이것은 O(n) 으로 표현이 가능하므로 시간 복잡도는 O(n)이다.


//예를 들어 
//      7
//   6    5
//  8 3  5 9
// 1 6
//
//의 트리가 있을때, 실제로 8~ 7까지만 보면 된다.
//그래서 자식 노드를 비교해보면,
//
//8은 1,6보다 크므로 바꾸지 않고,
//5는 자식노드 9보다 작으므로 9와 바꿔준다.
//9를 기준으로 9의 부모노드 7은 9보다 작으므로 바꿔준다.
//6은 8보다 작으므로 바꿔준다.
//마지막 9는 크니까 바꾸지 않고 가만히 냅둔다.


// => 이렇게 힙구조가 만들어졌다면, 
//가장 위쪽의 큰값과 가장 마지막 원소의 값과 바꿔준다.
//이제 집합의 크기를 줄여서 마지막 가장 큰 값을 빼고 나머지로 또 힙구조를 만든다.... 반복




//힙 노드 하나 정렬은 log N이 걸리고 이것을 n만큼 해주므로, 전체 시간 복잡도는 n log N이다

/*

#include<iostream>

using namespace std;

int number = 9;

int heap[9] = { 7,6,5,8,3,5,9,1,6 };

int main(){
	// 전체 트리 구조를 힙구조로 바꿔준다.

	for (int i = 1; i < number; i++) {
		int c = i;

		do {
			int root = (c - 1) / 2;
			if (heap[root] < heap[c]) {
				int temp = heap[root];
				heap[root] = heap[c];
				heap[c] = temp;
			}
			c = root;
		} while (c != 0);
	}
	// 해당 원소에 대해 뿌리까지 검사하기.

	for (int i = number - 1; i >= 0; i--) {
		int temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;

		int root = 0;
		int c = 1;

		do {
			c = 2 * root + 1;

			if (heap[c] < heap[c + 1] && c < i - 1) {
				c++;
			}
			if (heap[root] < heap[c] && c < i) {
				int temp = heap[root];
				heap[root] = heap[c];
				heap[c] = temp;
			}
			root = c;
		} while (c < i);
	}

	for (int i = 0; i < number; i++) {
		cout << heap[i] << ' ';
	}
}
*/


