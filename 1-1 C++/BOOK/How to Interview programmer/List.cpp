#include <list>
#include <iostream>

//typedef struct ListElement {
//    struct ListElement* next;
//    int data;
//}ListElement;

//단일 리스트
class IntElement {
public:
    IntElement(int value):next(NULL), data(value){}
    ~IntElement(){}

    IntElement* getNext() const{ return next; }
    int value() const { return data; }
    void setNext(IntElement* elem) { next = elem; }
    void setValue(int value) { data = value; }

public:
    IntElement* next;
    int data;
};


template <class T>
class ListElement {
public:
    //IntElement(int value):next(NULL), data(value){}
    ListElement(const T& value) :next(NULL), data(value) {}

    ~ListElement() {}

    ListElement* getNext() const { return next; }
    const T& value() const { return data; }
    void setNext(ListElement* elem) { next = elem; }
    void setData(const T& value) { data = value; }

private:
    ListElement* next;
    T data;
};

//bool insertInFront(IntElement *head, int data)
//{
//    IntElement* newElem = new IntElement;
//    if (!newElem) return false;
//
//    newElem->data = data;
//    newElem->next = head;
//    head = newElem; // 틀렸다! -> 머리 포인터 지역 변수만 바꾼다.
//    return true;
//}


//원소의 삽입 삭제
bool deleteElement(IntElement** head, IntElement* deleteMe)
{
    IntElement* elem;
    if (!head || !*head || !deleteMe)
        return false; //널 포인트 확이

    elem = *head;
    if (deleteMe == *head) { //삭제하려는 주소와 head의 주소가 동일하다면, (head삭제시?)
        *head = elem->next; 
        free(deleteMe);
        return true;
    } //헤드의 주소를 다음 주소로 바꿔준뒤, 삭제하려는 주소 메모리 해제

    while (elem) {
        if (elem->next == deleteMe) // elem이 deleteMe의 앞 원소라면?
        {
            elem->next = deleteMe->next;
            free(deleteMe);
            return true;
        }

        elem = elem->next;
    }

    return false; // deleteMe 못찾았을때
}


//만약 연결리스트의 모든 원소를 삭제해야하는 문제가 발생한다면
// 1) 다음 포인터로 넘어가 이전의 원소를 제거하는 것이 먼저일까
// 2) 원소를 제거하고 다음 원소로 넘어가는 것이 먼저일까?

// -> 1)의 경우에는 제거해야할 원소의 포인터를 덮어쓴 상황이기 떄문에 메모리 할당이 불가
// -> 2)의 경우에는 제거를 먼저해버리면 다음 next에 대한 포인터가 없어, 넘어가는 것이 불가능


//그래서 아래와 같이 포인터를 두개 쓴다.
void deleteList(IntElement** head)
{
    IntElement* deleteMe = *head;

    while (deleteMe)
    {
        IntElement* next = deleteMe->next;
        free(deleteMe);
        deleteMe = next;
    }
    *head = NULL;
}

int main()
{
    std::cout << "Hello World!\n";
}

