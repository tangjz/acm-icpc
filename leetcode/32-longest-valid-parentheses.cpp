class Solution {
public:
    int longestValidParentheses(string s) {
        int n = (int)s.length();
        stack<int> stk;
        stk.push(-1); // initial obstacle
        int ans = 0;
        for(int i = 0; i < n; ++i)
            if(s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if(stk.empty()) {
                    stk.push(i); // rightmost obstacle
                } else {
                    ans = max(ans, i - stk.top());
                }
            }
        return ans;
    }
};
