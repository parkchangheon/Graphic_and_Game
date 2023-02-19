#include<vector>
#include<iostream>
#include<chrono>
#include<thread>
#include<memory>
#include<mutex>
using namespace std;

const int MaxCount = 15000;
const int ThreadCount = 4;

// 우선 싱글 스레드 방식으로 처리해봄
// Single Thread First

bool IsPrimeNumber(int num)
{
	if (num == 1)
		return false;

	else if (num == 2 || num == 3)
		return true;

	for (int i = 2; i < num-1; i++)
	{
		if (num % i == 0)
			return false;
	}
	return true;
}


void PrintPrimeNumber(const vector<int>& numbers)
{
	for (auto i : numbers)
		cout << i << " ";
}

//싱글스레드(SingleTHread)
//int main()
//{
//	vector<int> primes;
//	auto t0 = chrono::system_clock::now(); // 함수를 통해 현재 시각 구함
//
//	for (int i = 0; i <= MaxCount; i++)
//	{
//		if (IsPrimeNumber(i))
//		{
//			primes.push_back(i);
//		}
//	}
//
//	auto t1 = chrono::system_clock::now();
//	auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
//	cout << "Took" << duration << " miliseconds" << endl;
//	PrintPrimeNumber(primes);
//}



//Use Multi Thread ==>error has pop up

void MutexEx0()
{
	int num = 1;
	vector<int> primes;

	auto t0 = chrono::system_clock::now();
	vector<shared_ptr<thread>>threads;

	for (int i = 0; i < ThreadCount; i++)
	{
		shared_ptr<thread> thread(new thread([&]() {

			//각 스레드의 메인 함수
			//값을 가져올 수 있으면 루프를 돈다.

			while (true)
			{
				int n;
				n = num;
				num++;

				if (n >= MaxCount) break;

				if (IsPrimeNumber(n))
				{
					primes.push_back(n);
				}

			}
		}));
		//스레드 객체를 일단 갖는다.
		threads.push_back(thread);
	}

	for (auto thread : threads)
		thread->join();


	auto t1 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
	cout << "Took" << duration << " miliseconds" << endl;
	PrintPrimeNumber(primes);

}


//그러나 race condition 문제에 봉착할 수 있다.
/*
여러 스레드/프로세스가 공유 자원에 동시에 접근하려 할때 일어나는 경쟁상황
그런데, 컨택스트 스위칭은 일정하게 일어나지 않는다.
그래서 결과 값이 달라질 수 있다.
*/


//이것을 해결하기 위한 방법이 임계영역 - 뮤택스이다.
/*
1. x,y를 보호하는 뮤텍스 MX를 제작
2. 스레드는 x,y를 건드리기 전에 MX에 사용권을 요청
3. 스레드는 x,y를 액세스 한다.
4. 액세스가 끝나면 MX에 사용권을 놓는것을 요청
*/

void MutexEx()
{
	std::mutex mx;
	mx.lock();  //여기서 사용권을 획득하면 다음 단계로 넘어간다.

	//read(x); ==> 만약 여기서 throw를 하면 아랫 부분은 실행이 불가능하니, try-catch를 쓰기도하는데, 너무 귀찮다. ==>로컬 변수 파괴시, 자동 unlock해주게 해보자
	//write(y);
	//sum(x); ==> 사용 단계

	mx.unlock(); // 사용권을 놓아준다.
}



void MutexEx2()
{
	std::recursive_mutex mx;
	lock_guard<recursive_mutex> lock(mx); //lock 객체가 사라질때 자동으로 unlock이 실행된다.
	//read(x);
	//write(x);
	//sum(x);

}



// mutex를 활용한 multithreading code

int main() {
	int num = 1;
	recursive_mutex num_mutex; //일반 mutex보다 재귀적인 소유권을 가짐.

	vector<int>primes;
	recursive_mutex primes_mutex;

	auto t0 = chrono::system_clock::now();

	vector<shared_ptr<thread>> threads;
	
	for (int i = 0; i < ThreadCount; i++)
	{
		shared_ptr<thread> thread(new thread([&]() {
			while (true)
			{
				int n;
				{
					lock_guard<recursive_mutex> num_lock(num_mutex);
					n = num;
					num++;
				}

				if (n >= MaxCount) break;

				if (IsPrimeNumber(n))
				{
					lock_guard<recursive_mutex> primes_lock(primes_mutex);
					primes.push_back(n);
				}
			}
		}));

		threads.push_back(thread);
	}

	for (auto thread : threads)
	{
		thread->join();
	}

	auto t1 = chrono::system_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
	cout << "Took" << duration << " miliseconds" << endl;
	PrintPrimeNumber(primes);

}


// 스레드 하나일떄랑 스레드 4개일때랑 소요 되는 시간이 4배 줄어들지는 않음
// cpu는 여러개이지만, 결국 cpu는 메모리에 접근하게된다.
// 그렇다면 뮤텍스를 잘게 나누는 것이 낫지 않나 싶을텐데 
// 오히려 프로그램 성능이 떨어진다. => 액세스 과정이 무겁기때문.
// 또한 프로그램이 매우 복잡해진다. (교착상태 문제 발생 가능)



