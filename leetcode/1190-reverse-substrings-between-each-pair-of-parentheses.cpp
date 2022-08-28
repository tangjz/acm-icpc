class Solution {
    string solve(int L, int R, string const &s, vector<int> const &pR) {
        string ret = "";
        for(int i = L; i <= R; ++i) {
            if(s[i] == '(') {
                string tmp = solve(i + 1, pR[i] - 1, s, pR);
                reverse(tmp.begin(), tmp.end());
                ret += tmp;
                i = pR[i];
            } else {
                ret.push_back(s[i]);
            }
        }
        return ret;
    }
public:
    string reverseParentheses(string s) {
        int n = s.size();
        vector<int> pR(n, -1);
        stack<int> stk;
        for(int i = 0; i < n; ++i)
            if(s[i] == '(') {
                stk.push(i);
            } else if(s[i] == ')') {
                pR[stk.top()] = i;
                stk.pop();
            }
        return solve(0, n - 1, s, pR);
    }
};
