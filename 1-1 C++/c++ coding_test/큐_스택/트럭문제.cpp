//내풀이
/*
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int time = weight;
    vector<int> finish_truck;
    queue <pair<int, int>> now_ing; //들어간 트럭의 무게 & 소요 시간(--해줌)

    while (!truck_weights.empty())
    {
        int next_truck = truck_weights.front();

        if (!now_ing.empty()) {
            if (now_ing.front().second < 0) {
                finish_truck.push_back(now_ing.front().first);
                bridge_length += 1;
                weight += now_ing.front().first;
            }
        }


        if (bridge_length > 0 && weight >= next_truck)
        {
            now_ing.push(make_pair(next_truck, time--));
            bridge_length -= 1;
            weight -= next_truck;
        }



        answer++;
    }


    return answer;
}
*/



#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;

    int idx = 0; //차량 지목용 인덱스
    int sum = 0; //현재 다리에 올라와있는 차량 무게 총합
    queue<int> now_ing; // 현재 다리를 건너는 트럭 체크 큐

    while (1)
    {
        if (idx == truck_weights.size())  //마지막 트럭일때
        {
            answer += bridge_length;
            break;
        }

        answer++; //시간초 증가

        int tmp = truck_weights[idx];

        //트럭이 다리를 건넜을때,
        if (now_ing.size() == bridge_length) //현재 다리 길이 (0으로 채워서) = 다리 전체 길이
        {
            sum -= now_ing.front(); //다리 무게에서 트럭 무게 빼주고
            now_ing.pop();          //다리 스택에서 트럭을 pop
        }

        if (sum + tmp <= weight) //다음차가 진입할 수 있다면
        {
            now_ing.push(tmp);
            sum += tmp;
            idx++;
        }
        else
            now_ing.push(0); // 진입이 불가능하다면, 그냥 카운터만 올린다. (0을 넣어줌으로써, 큐에 경과 시간 체크)

    }


    return answer;
}