#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0, count = 0;
    queue <pair<int, int>> queue; //일반 큐
    priority_queue<int> pri_queue; //우선순위 큐

    //셋업 작업
    for (int i = 0; i < priorities.size(); i++)
    {
        queue.push(make_pair(i, priorities[i]));  //큐에 들어온 순서와 중요도를 삽입
        //우선순위 큐에 넣는다.
        pri_queue.push(priorities[i]);
    }

    //큐가 빌때까지 반복
    while (!queue.empty())
    {
        int index = queue.front().first;
        int value = queue.front().second;
        queue.pop();

        //우선순위 1순위와 현재값이 같다면,
        if (pri_queue.top() == value)
        {
            pri_queue.pop(); //우선 순위 큐 pop
            count++; //하나가 나갔으니, 카운트를 올려준다.

            if (index == location) {
                answer = count;
                break;
            }

        }

        else
            queue.push(make_pair(index, value));



    }



    return answer;
}