//DP알고리즘

//#include <string>
//#include <vector>
//#include <iostream>
//using namespace std;
//
//int solution(vector<vector<int>> triangle) {
//    int answer = 0;
//
//    for (int i = triangle.size() - 1; i > 0; i--)
//    {
//        for (int j = 0; j < triangle[i].size() - 1; j++)
//        {
//            if (triangle[i][j] > triangle[i][j + 1])
//                triangle[i - 1][j] += triangle[i][j];
//            else
//                triangle[i - 1][j] += triangle[i][j + 1];
//        }
//    }
//
//    answer = triangle[0][0];
//    return answer;
//}
//
//
//int main()
//{
//    vector<vector<int>> v = { {7},{3,8},{8,1,0},{2,7,4,4},{4,5,2,6,5 } };
//    cout << solution(v);
//}