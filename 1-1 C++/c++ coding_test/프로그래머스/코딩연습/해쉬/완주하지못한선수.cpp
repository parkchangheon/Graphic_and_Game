#include <string>
#include <vector>
#include<iostream>
#include<algorithm>


using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";

    for (int i = 0; i < completion.size(); i++)
    {
        auto it = find(participant.begin(), participant.end(), completion[i]);
        participant.erase(it);
    }
    answer = participant[0];

    
    return answer;
}


int main()
{
    vector<string> p1 = { "leo", "kiki", "eden" };
    vector <string> c1 = { "eden", "kiki" };
    string res1 = solution(p1, c1);
    cout << res1<<endl;

    vector<string> part = { "marina", "josipa", "nikola", "vinko", "filipa" };
    vector<string> comp = { "josipa", "filipa", "marina", "nikola" };
    string res = solution(part, comp);
    cout << res<<endl;


    vector<string> part2 = { "mislav", "stanko", "mislav", "ana" };
    vector<string> comp2 = { "stanko", "ana", "mislav" };
    string res2 = solution(part2, comp2);
    cout << res2;
}