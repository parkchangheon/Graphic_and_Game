/*
//기능 개발
#include<iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {

    int n = progresses.size();
    int* arr_p = new int[n];
    int* arr_s = new int[n];
    vector<int>answer;

    for (int i = n - 1; i >= 0; i--) {
        arr_p[i] = progresses.back();
        arr_s[i] = speeds.back();

        progresses.pop_back();
        speeds.pop_back();
    }
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        if (arr_p[i] > 100)
        {
            if(tmp!=0)
                tmp += 1;
        }

        else {
            if (tmp != 0) {
                answer.push_back(tmp);
                tmp = 0;
            }

            while (arr_p[i] <= 100) {
                for (int j = 0; j < n; j++) {
                    arr_p[j] += arr_s[j];
                }
            }
            if (arr_p[i] > 100)
                tmp += 1;
            
        }
    }
    if (tmp != 0)
        answer.push_back(tmp);
    

    return answer;
}

int main() {
    vector<int> p_one = { 93,30,55 };
    vector<int> s_one = { 1,30,5 };

    vector<int> p_two = { 95,90,99,99,80,99 };
    vector<int> s_two = { 1,1,1,1,1,1 };

    vector<int> r_one = solution(p_one, s_one);
    vector<int> r_two = solution(p_two, s_two);

    for (int i = 0; i < r_one.size(); i++)
        cout << r_one[i] << " ";
    cout << endl;

    for (int i = 0; i < r_two.size(); i++)
        cout << r_two[i] << " ";
}
*/
