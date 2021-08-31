//이진트리

//완전 이진 트리의 경우 배열로 구현이 가능하지만, 아닐 경우엔 포인터를 사용하는게 편하다.( 데이터 낭비도 x)

//#include<iostream>
//
//using namespace std;
//
//int number = 15;
//
////하나의 노드정보를 선언한다.
//typedef struct node* treePointer;
//typedef struct node {
//	int data;
//	treePointer leftChild, rightChild;
//}node;
//
//
////전위 순회를 구현합니다.
//void preorder(treePointer ptr) {
//	if (ptr) {
//		cout << ptr->data << ' ';
//		preorder(ptr->leftChild);
//		preorder(ptr->rightChild);
//	}
//}
//
////중위 순회를 구현합니다.
//void inorder(treePointer ptr) {
//	if (ptr) {
//		inorder(ptr->leftChild);
//		cout << ptr->data << ' ';
//		inorder(ptr->rightChild);
//	}
//}
//
//
////후위 순회를 구현합니다.
//void postorder(treePointer ptr) {
//	if (ptr) {
//		postorder(ptr->leftChild);
//		postorder(ptr->rightChild);
//		cout << ptr->data << ' ';
//	}
//}
//
//
//
//int main(void) {
//	node nodes[16];
//	for (int i = 0; i <= number; i++) {
//		nodes[i].data = i;
//		nodes[i].leftChild = NULL;
//		nodes[i].rightChild = NULL;
//	}
//
//	//연결하는 파트 ( to 부모노드 )
//	for (int i = 0; i <= number; i++) {
//		if (i % 2 == 0) {
//			nodes[i / 2].leftChild = &nodes[i];
//		}
//		else {
//			nodes[i / 2].rightChild = &nodes[i];
//		}
//	}
//
//
//	preorder(&nodes[1]);
//	return 0;
//}