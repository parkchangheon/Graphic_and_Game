// Interview_Book.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

//#include <iostream>
//using namespace std;
//
//class IntElement {
//public:
//	IntElement(int value) :next(NULL), data(value) {}
//	~IntElement() {}
//
//	IntElement* getNext() const { return next; }
//	int value() const { return data; }
//	void setNext(IntElement* elem) { next = elem; }
//	void setValue(int value) { data = value; }
//
//
//private:
//	IntElement* next;
//	int data;
//};
//


//template<class T>
//class ListElment {
//
//private:
//	ListElement* next;
//	T data;
//public:
//	ListElement(const T& Value) :next(NULL), data(value) {}
//	~ListElement{}
//
//	ListElement* getNext()const { return next; }
//	const T& value() const { return data; }
//	void setNext(ListElement* elem) { next = elem; }
//	void setData(const T* value) { data = value; }
//
//
//
//	//public void insertInFront(ListElement<integer>list, int data) {
//	//	ListElement < Integer>1 = new ListElement<Integer>(data);
//	//	1.setNext(list);
//	//}
//
//
//	public ListElement<Integer> insertInFront(ListElement<Integer>list, int data)
//	{
//		ListElement < Integer>1 = new ListElement<Integer>(data);
//		1.setNext(list);
//		return 1;
//	}
//	
//};







//#include<iostream>
//
//using namespace std;
//
//typedef struct IntElement {
//private:
//	IntElement* next;
//	int data;
//
//public:
//	IntElement(int value):next(NULL),data(value) {}
//	~IntElement() {}
//
//	IntElement* getNext() const { return next; }
//	int value() const { return data; }
//	void setNext(IntElement* elem) { next = elem; }
//	void setValue(int value) { data = value; }
//};
//
//bool insertInFront(IntElement** head, int data) {
//	IntElement* newElem = malloc(sizeof(IntElement));
//	if (!newElem)
//		return false;
//
//	newElem->setValue(data);
//	newElem->setNext(*head);
//	*head = newElem;
//	return true;
//}




//#include<iostream>
//using namespace std;
//
//
//
///// <summary>
///// 헤더 파일
///// </summary>
//
//
//struct Node {
//	int data;
//	struct Node* link; // 이 구조체 자체를 가리키는 포인터
//};
//
//struct HeadNode {
//	Node* head;
//};
//
//class Singlist {
//public:
//	HeadNode* createList() {          // 리스트 생성, 헤드 노드
//		HeadNode* H = new HeadNode;   // 헤드노드를 가리키는 포인터 H
//		H->head = NULL;				  //헤드 초기화
//		return H;
//	}
//
//	//리스트의 마지막에 노드 삽입
//	void addNode(HeadNode* H, int x)
//	{
//		Node* NewNode = new Node;  //새로 추가할 노드
//		Node* LastNode;            //원래 있던 노드의 마지막 노드
//		NewNode->data = x;         
//		NewNode->link = NULL;
//
//		if (H->head == NULL) {  //리스트가 비어있다면,
//			H->head = NewNode;
//			return;
//		}
//
//		LastNode = H->head;     // 리스트가 비어있지 않다면 가장 처음 노드가 LastNode를 가리킨다.
//		while (LastNode->link != NULL) // 연결리스트의 마지막 노드를 찾는 과정
//			LastNode = LastNode->link; 
//		LastNode->link = NewNode;// 마지막 노드를 찾고 While문 나온다면 뒤에 새 노드를 가리킨다.
//	}
//
//	//리스트의 마지막 노드 삭제 
//	void deleteNode(HeadNode* H)
//	{
//		Node* prevNode; //삭제되는 노드 바로 앞 노드
//		Node* delNode;  //삭제되는 노드
//		
//		if (H->head == NULL) //리스트가 비어있는 경우
//			return;
//		if (H->head->link == NULL) // 한개의 노드만을 가지고 있을때
//		{
//			delete H->head; // 가리키고 있는 노드 해제한다.
//			H->head = NULL; // 헤더의 포인터를 널값으로 바꿔준다.
//			return;
//		}
//		else {   // 다수 존재할때
//			prevNode = H->head; //헤드 노드가 가리키는 노드가 prevNode가 되게 설정
//			delNode = H->head->link; //prevNode 다음 위치로 delNode 설정
//
//			while(delNode->link!=NULL) // del 노드가 마지막 노드가 될때까지
//			{
//				prevNode = delNode; //prevNode를 한칸씩 가고
//				delNode = prevNode->link; // delNode도 한깍씩 끝으로 보낸다.
//			}
//			// 가고 나서 해제시,
//			free(delNode); //마지막 노드의 메모리 공간을 반환
//			prevNode->link = NULL; // 마지막 전 노드는 NULL로 보내줌.
//		}
//	}
//	
//
//	//리스트의 특정 노드 삭제
//	void deleteThisNode(HeadNode* H, int deldata)
//	{
//		Node* delNode;
//		Node* prevNode;
//		prevNode = H->head;
//
//		while (prevNode->link->data != deldata)  //특정 데이터와 같지 않다면 계속해서 밀어낸다.
//			prevNode = prevNode->link;
//
//		delNode = prevNode->link;      //prevNode가 가리키는 노드가 삭제할 노드다.
//		prevNode->link = delNode->link;//prevNode는 삭제할 노드가 가리키던 노드를 가리킨다.
//		free(delNode); //delNode삭제
//		cout << deldata << " 데이터 값을 가진 노드가 삭제되었습니다." << endl;
//		return;
//	}
//
//
//	//리스트에 특정 노드 삽입
//	void addThisNode(HeadNode* H, int afterthisdata, int adddata)
//	{
//		//after this 노드 이후에 adddata를 삽입하고자 한다.
//		Node* prevNode;
//		prevNode = H->head;
//
//		while (prevNode->data != afterthisdata) {
//			prevNode = prevNode->link;
//		}
//		
//		Node* NewNode = new Node;
//		NewNode->data = adddata;
//		NewNode->link = prevNode->link;
//		prevNode->link = NewNode;
//		return;
//	}
//
//	//특정 노드 검색
//	void searchNode(HeadNode* H, int thisdata) {
//		Node* someNode;
//		someNode = H->head;
//
//		while (someNode->data != thisdata) {
//			someNode = someNode->link;
//		}
//		cout << thisdata << " 데이터를 검색하는데 성공했습니다." << endl;
//	}
//
//	//연결리스트 출력
//	void printList(HeadNode* L)
//	{
//		Node* p;
//		cout << "연결리스트 목록 = (";
//		p = L->head;
//
//		while (p != NULL) {
//			cout << p->data;
//			p = p->link;
//			if (p != NULL)
//				cout << "==>";
//		}
//		cout << ")" << endl;
//	}
//};
//
//// cpp 파일
//
//int main()
//{
//	Singlist list;
//	HeadNode* L;
//	L = list.createList();
//
//	cout << "1. 빈 연결리스트를 생성하였다." << endl << endl;
//
//	int data1, data2, data3;
//	cout << "2. 연결리스트에 추가할 노드의 데이터를 3개 정해주세요:";
//	cin >> data1 >> data2 >> data3;
//	list.addNode(L, data1);
//	list.printList(L);
//	list.addNode(L, data2);
//	list.printList(L);
//	list.addNode(L, data3);
//	list.printList(L);
//
//	cout << endl;
//
//	cout << "3. 탐색할 노드의 데이터를 정해주세요 : ";
//	int data4;
//	cin >> data4;
//	list.searchNode(L, data4);
//
//	cout << endl;
//	cout << "4-1. 어떤 노드 뒤에 노드를 추가할건가요? ";
//	int data5, data6;
//	cin >> data5 >> data6;
//	list.addThisNode(L, data5, data6);
//	list.printList(L);
//	cout << endl;
//
//	cout << "5. 삭제하고자 하는 노드를 알려주세요 : ";
//	int data7;
//	cin >> data7;
//	list.deleteThisNode(L, data7);
//	list.printList(L);
//	cout << endl;
//
//	cout << "6. 마지막 노드를 삭제합니다." << endl;
//	list.deleteNode(L);
//	list.printList(L);
//	cout << endl;
//
//	cout << "피곤하니까 연산을 끝내겠습니다." << endl;
//
//}