#include<string>
#include <iostream>
#include <stack>

using namespace std;

bool solution(string s)
{
    bool answer = true;
    stack<char> stack;

    if (s[0] == ')')
        return false;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
            stack.push(s[i]);
        else
        {
            if (stack.empty())
                return false;
            else
                stack.pop();
        }
    }

    if (!stack.empty())
        answer = false;


    return answer;
}