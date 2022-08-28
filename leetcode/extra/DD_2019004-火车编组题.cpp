#include <bits/stdc++.h>
using namespace std;

bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    stack<int> stk;
    auto it = pushed.begin(), jt = popped.begin();
    while(jt != popped.end()) {
        while(it != pushed.end() && (stk.empty() || stk.top() != *jt))
            stk.push(*(it++));
        if(stk.empty() || stk.top() != *jt)
            return 0;
        stk.pop();
        ++jt;
    }
    return 1;
}

int main() {
    vector<int> pushed(4), popped(4);
    iota(pushed.begin(), pushed.end(), 1);
    for(int i = 0; i < 4; ++i)
        scanf("%d", &popped[i]);
    puts(validateStackSequences(pushed, popped) ? "Yes" : "No");
    return 0;
}
