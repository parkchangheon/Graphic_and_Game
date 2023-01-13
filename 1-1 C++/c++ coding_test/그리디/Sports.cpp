//#include <string>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//int solution(int n, vector<int> lost, vector<int> reserve) {
//    int answer = 0;
//    int lost_count = 0;
//    int reserve_count = 0;
//
//    answer = n - lost.size();
//    sort(lost.begin(), lost.end());
//    sort(reserve.begin(), reserve.end());
//
//
//    while (1)
//    {
//        if (reserve_count == reserve.size() || lost_count == lost.size())
//            break;
//
//        if (lost[lost_count] > reserve[reserve_count])
//        {
//            if (reserve[reserve_count] + 1 == lost[lost_count])
//            {
//                answer += 1;
//                lost_count++;
//                reserve_count++;
//            }
//
//
//            if (reserve[reserve_count] + 1 < lost[lost_count])
//            {
//                reserve_count++;
//            }
//        }
//
//        else
//        {
//            if (reserve[reserve_count] - 1 == lost[lost_count])
//            {
//                answer += 1;
//                lost_count++;
//                reserve_count++;
//            }
//
//
//            if (reserve[reserve_count] - 1 > lost[lost_count])
//            {
//                lost_count++;
//            }
//
//
//        }
//
//    }
//
//
//    return answer;
//}



#include <string>
#include <vector>

using namespace std;
int student[35];
int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    for (int i : reserve) student[i] += 1;
    for (int i : lost) student[i] += -1;
    for (int i = 1; i <= n; i++) {
        if (student[i] == -1) {
            if (student[i - 1] == 1)
                student[i - 1] = student[i] = 0;
            else if (student[i + 1] == 1)
                student[i] = student[i + 1] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
        if (student[i] != -1) answer++;

    return answer;
}