#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

int solution(vector<int> nums)
{
    unordered_map<int, int> pokMap;
    int answer = 0;
    int n = nums.size();
    int m = n / 2;

    sort(nums.begin(), nums.end());
    for (auto elem : nums)
    {
        if (answer < m) {
            if (pokMap.end() == pokMap.find(elem)) {
                pokMap.insert(make_pair(elem, 1));
                answer++;
            }
        }
        else
            break;
    }
    cout << answer << endl;

    return answer;
}