class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> stk;
        stk.push(0);
        for(char ch: s)
            if(ch == '(') {
                stk.push(0);
            } else {
                int v = stk.top();
                stk.pop();
                stk.top() += max(v << 1, 1);
            }
        return stk.top();
    }
};
