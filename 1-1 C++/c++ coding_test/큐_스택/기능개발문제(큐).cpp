#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> q;

    for (int i = 0; i < progresses.size(); ++i)
    {
        if ((100 - progresses[i]) % speeds[i] == 0)    //한번에 나눠떨어지면 ~
            q.push((100 - progresses[i]) / speeds[i]);

        else                                    //나눠떨어지지 않으면 하루 더 추가.
            q.push((100 - progresses[i]) / speeds[i] + 1);
    }


    while (!q.empty())
    {
        int cnt = 1;
        int current = q.front();
        q.pop();
        while (!q.empty() && q.front() <= current)
        {
            cnt++;
            q.pop();
        }
        answer.push_back(cnt);

    }

    return answer;
}