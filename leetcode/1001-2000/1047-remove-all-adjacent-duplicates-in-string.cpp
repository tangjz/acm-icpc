class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> stk;
        for(char ch: s) {
            if(stk.empty() || stk.top() != ch) {
                stk.push(ch);
            } else {
                stk.pop();
            }
        }
        s = "";
        while(!stk.empty()) {
            s.push_back(stk.top());
            stk.pop();
        }
        reverse(s.begin(), s.end());
        return s;
    }
};
