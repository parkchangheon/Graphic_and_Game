//DWORD threadID;
//ThreadParam threadParam;
//threadParam.value = 123;
//CreateThread(
//	ThreadProc, &threadParam, &threadId
//);



//InGame MultiThreading
//#include<iostream>
//using namespace std;
//
//void Render() { ; }
//void LoadModel1() { ; }
//void LoadTexture() { ; }
//void LoadAnimation() { ; }
//void LoadSound() { ; }
//void FrameMove() { ; }
//
//void LoadScene()
//{
//	Render();
//	LoadScene();
//	Render();
//	LoadModel1();
//	Render();
//	LoadTexture();
//	Render();
//	LoadAnimation();
//	Render();
//	LoadSound();
//} //씬을 로드하는 좋지 않는 방법 --> 멀티스레딩을 하지 않았을 때
//
//
//// 반면 멀티 스레딩을 최대한 활용하는 방법 
//int main()
//{
//	bool isStillLoading;
//
//	{ //Thread1
//		isStillLoading = true;
//		while (isStillLoading){ //로딩 상황 일떄 
//			FrameMove();
//			Render();
//		}
//	}
//
//
//	{ //Thread2  --> 게임에서 필요한 데이터를 디스크에서 로딩한다.
//		// 로딩 종료 후 특정 변수를 변경한다.
//		LoadScene();
//		LoadModel1();
//		LoadTexture();
//		LoadAnimation();
//		LoadSound();
//
//	}
//}



// 플레이어 정보를 읽거나 쓰려고 디스크를 액세스 하는 경우, 
// 디스크를 액세스하는 스레드는 디스크의 처리 결과가 끝날 때 까지 기다려야 한다. ==> 이때 CPU가 노는데, 이 노는 시간을 다른 플레이어에게 분배
