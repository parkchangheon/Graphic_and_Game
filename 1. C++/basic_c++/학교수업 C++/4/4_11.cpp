//#include<iostream>
//using namespace std;
//
//class Container {
//    int size;     
//public:
//    Container() { size = 10; }
//    void fill();                
//    void consume();                 
//    int getSize();                
//};
//
//class CoffeeVendingMachine {   
//    Container tong[3];            
//    void fill();
//    void selectEspresso();
//    void selectAmericano();
//    void selectSugarCoffee();
//    void show();                
//public:
//    void run(); 
//};
//
//int start = 0;
//
//void Container::fill() {
//    size = 10;
//}
//void Container::consume() {
//    size--;
//}
//int Container::getSize() {
//    return size;
//}
//
//void CoffeeVendingMachine::run() {
//    int num;
//    if (start == 0)
//        cout << "***** 커피 자판기를 작동합니다. *****\n";
//    start++;
//    while (true) {
//        cout << "메뉴를 눌러주세요(1:에스프레소, 2:아메리카노, 3:설탕커피, 4:잔량보기, 5:채우기)>> ";
//        cin >> num;
//        switch (num) {
//        case 1:
//            selectEspresso();
//            break;
//        case 2:
//            selectAmericano();
//            break;
//        case 3:
//            selectSugarCoffee();
//            break;
//        case 4:
//            show();
//            break;
//        case 5:
//            fill();
//            break;
//        }
//    }
//}
//
//void CoffeeVendingMachine::selectEspresso() {
//    for (int i = 0; i < 3; i++) {
//        if (tong[i].getSize() == 0) {
//            cout << "원료가 부족합니다.\n";
//            run();
//        }
//    }
//    tong[0].consume();
//    tong[1].consume();
//    cout << "에스프레소 드세요\n";
//}
//
//void CoffeeVendingMachine::selectAmericano() {
//    for (int i = 0; i < 3; i++) {
//        if (tong[i].getSize() == 0) {
//            cout << "원료가 부족합니다.\n";
//            run();
//        }
//    }
//    tong[0].consume();
//    tong[1].consume(); tong[1].consume();
//    cout << "아메리카노 드세요\n";
//}
//
//void CoffeeVendingMachine::selectSugarCoffee() {
//    for (int i = 0; i < 3; i++) {
//        if (tong[i].getSize() == 0) {
//            cout << "원료가 부족합니다.\n";
//            run();
//        }
//    }
//    tong[0].consume();
//    tong[1].consume(); tong[1].consume();
//    tong[2].consume();
//    cout << "설탕커피 드세요\n";
//}
//
//void CoffeeVendingMachine::show() {
//    cout << "커피 " << tong[0].getSize();
//    cout << ", 물 " << tong[1].getSize();
//    cout << ", 설탕 " << tong[2].getSize() << endl;
//}
//
//void CoffeeVendingMachine::fill() {
//    for (int i = 0; i < 3; i++) {
//        tong[i].fill();
//    }
//    show();
//}
//
//int main() {
//    CoffeeVendingMachine* coffee = new CoffeeVendingMachine;
//    coffee->run();
//    delete coffee;
//}
