class Solution {
    int calc(int L, int R, string const &s, vector<int> const &pR) {
        int ret = 0;
        char op = '+';
        while(L <= R) {
            for( ; L <= R && s[L] == ' '; ++L);
            if(L > R)
                break;
            if(s[L] == '-' || s[L] == '+') {
                op = s[L++];
                continue;
            }
            int val;
            if(s[L] == '(') {
                val = calc(L + 1, pR[L] - 1, s, pR);
                L = pR[L] + 1;
            } else {
                int M;
                for(M = L++; s[L] >= '0' && s[L] <= '9'; ++L);
                val = stoi(s.substr(M, L - M));
            }
            ret += op == '+' ? val : -val;
        }
        return ret;
    }
public:
    int calculate(string s) {
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
        return calc(0, n - 1, s, pR);
    }
};
