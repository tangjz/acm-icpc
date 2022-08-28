class Solution {
public:
    int minimumTime(string s) {
        int n = s.size();
        vector<int> suf(n + 1);
        stack<int> stk;
        suf[n] = 0;
        stk.push(n);
        for(int i = n - 1, c = 0; i > 0; --i) {
            c += s[i] == '1' ? -1 : 1;
            suf[i] = c;
            if(suf[i] < suf[stk.top()])
                stk.push(i);
        }
        int L = -1, R = stk.top(), best = suf[R];
        for(int i = 0, c = 0; i < n; ++i) {
            c += s[i] == '1' ? -1 : 1;
            if(stk.top() == i)
                stk.pop();
            int tmp = c + suf[stk.top()];
            if(best >= tmp) {
                best = tmp;
                L = i;
                R = stk.top();
            }
        }
        int ret = L + 1 + (n - R);
        for(int i = L + 1; i < R; ++i)
            if(s[i] == '1')
                ret += 2;
        return ret;
    }
};
