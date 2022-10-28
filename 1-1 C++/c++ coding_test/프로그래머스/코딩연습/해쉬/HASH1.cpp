//#include <string>
//#include <vector>
//#include<iostream>
//#include<algorithm>
//
//
//using namespace std;
//
////string solution(vector<string> participant, vector<string> completion) {
////    string answer = "";
////
////    sort(participant.begin(), participant.end());
////    sort(completion.begin(), completion.end());
////    for (int i = 0; i < completion.size(); i++)
////    {
////        if (participant[i] != completion[i])
////            return participant[i];
////    }
////    return participant[participant.size()-1];
////}
//
//#include<unordered_map>
//string solution(vector<string> participant, vector<string> completion) {
//    string answer = "";
//    unordered_map<string, int> strMap; //unordered_map은 중복된 데이터를 허용하지 않는다.->하지만 key가 유사한 데이터가 많을시, 해시 충돌로 인해 성능이 떨어질 수 있다.
//    for (auto elem : completion)
//    {
//        if (strMap.end() == strMap.find(elem))  //없으면 추가해주고
//            strMap.insert(make_pair(elem, 1));
//        else  //있으면 카운트를 올려주는 방식으로 
//            strMap[elem]++;
//    }
//
//    for (auto elem : participant)
//    {
//        if (strMap.end() == strMap.find(elem)) //없다면 현재 원소가 못완주한애다.
//        {
//            answer = elem;
//            break;
//        }
//
//        else {                                  // 있다면 얘는 하나 빼준다.
//            strMap[elem]--;
//            if (strMap[elem] < 0)
//            {
//                answer = elem;
//                break;
//            }
//        }
//    }
//
//    return answer;
//}
//
//
//int main()
//{
//    vector<string> parti = { "leo", "leo","kiki", "eden"};
//    vector<string> comp = { "eden", "kiki" };
//    solution(parti, comp);
//    //unordered_map<string, int> strMap;
//    //cout << strMap.size() << endl;
//    //
//    //for (auto elem : parti)
//    //{
//    //    if (strMap.end() == strMap.find(elem)) //end가 뜨면 없다는 뜻이다.
//    //        strMap.insert(make_pair(elem, 1));
//    //    else
//    //        strMap[elem]++; //있다면 카운트를 증가시켜준다.
//    //    
//    //}
//    //cout << strMap["kiki"]<<endl;
//    //cout << strMap["leo"]<<endl;
//    //cout << strMap.size() << " " << endl;
//}