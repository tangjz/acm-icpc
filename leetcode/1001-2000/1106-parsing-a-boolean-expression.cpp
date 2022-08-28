class Solution {
    bool solve(int L, int R, string const &e, vector<int> const &pR) {
        switch(e[L]) {
            case 't': case 'f':
                return e[L] == 't';
            case '!':
                return !solve(L + 2, R - 1, e, pR);
            case '&': case '|': {
                bool fir = e[L] == '&', ret = fir;
                for(int i = L + 1; i < R - 1; i = pR[i]) {
                    bool cur = solve(i + 1, pR[i] - 1, e, pR);
                    ret = e[L] == '&' ? ret && cur : ret || cur;
                    if(ret != fir)
                        break;
                }
                return ret;
            }
        }
        return 0;
    }
public:
    bool parseBoolExpr(string e) {
        int n = e.size();
        vector<int> pR(n, -1);
        stack<int> stk;
        for(int i = 0; i < n; ++i)
            if(e[i] == '(') {
                stk.push(i);
            } else if(e[i] == ',') {
                pR[stk.top()] = i;
                stk.pop();
                stk.push(i);
            } else if(e[i] == ')') {
                pR[stk.top()] = i;
                stk.pop();
            }
        return solve(0, n - 1, e, pR);
    }
};
