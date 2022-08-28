class Solution {
    int calc(int L, int R, string &s, vector<int> &pR) {
        int uL = L, uR = R;
        int ret = 0, adt = 0;
        char op = '+';
        if(s[L] == '(') {
            adt = calc(L + 1, pR[L] - 1, s, pR);
            L = pR[L] + 1;
        } else {
            for( ; s[L] >= '0' && s[L] <= '9'; ++L)
                adt = adt * 10 + (s[L] - '0');
        }
        while(L <= R) {
            char nxt = s[L++];
            int val = 0;
            if(s[L] == '(') {
                val = calc(L + 1, pR[L] - 1, s, pR);
                L = pR[L] + 1;
            } else {
                for( ; s[L] >= '0' && s[L] <= '9'; ++L)
                    val = val * 10 + (s[L] - '0');
            }
            switch(nxt) {
                case '+': case '-': {
                    switch(op) {
                        case '+': {
                            ret += adt;
                            break;
                        }
                        case '-': {
                            ret -= adt;
                            break;
                        }
                        default: assert(0);
                    }
                    adt = val;
                    op = nxt;
                    break;
                }
                case '*': {
                    adt *= val;
                    break;
                }
                case '/': {
                    adt /= val;
                    break;
                }
                default: assert(0);
            }
        }
        switch(op) {
            case '+': {
                ret += adt;
                break;
            }
            case '-': {
                ret -= adt;
                break;
            }
            default: assert(0);
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
