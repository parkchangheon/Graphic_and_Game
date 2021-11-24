
//#include<iostream>
//using namespace std;
//
//int main() {
//	//===================포인터 예제
//	//short sArr[10] = { 1,2,3,4,5,6,7,8,9,10 }; // short배열.
//	//int* pI = (int*)sArr; //강제 캐스팅해서 int 포인터로 받음.
//	//int iData = *((short*)(pI + 2));
//	//printf("1번 문제 정답 : %d \n", iData);
//
//	//char cArr[2] = { 1,1 };
//	//short* pS = (short*)cArr;
//	//iData = *pS;
//
//	//printf("2번 문제 정답 : %d\n", iData);
//	//return 0;
//
//
//	//=============================
//
//	const int cint = 100;
//	// 상수화 시켰다. 변경 불가
//
//	int a = 0;
//	int* pInt = &a;
//
//	*pInt = 1;
//	pInt = nullptr;
//
//	int b = 0;
//	const int* pConstInt = &a;
//	// 가리키고 있는 원본 변수를 상수화한거다
//	//*pConstInt =100;이 불가능하다.
//	pConstInt = &b; // 하지만 다른것을 가리키는건 가능
//
//
//	int* const pIntConst = &a; 
//	// 포인터가 가리키고 있는 주소를 상수화
//	*pIntConst = 400;
//	//pIntConst = &b; 
//
//}




