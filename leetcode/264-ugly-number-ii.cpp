class Solution {
public:
    int nthUglyNumber(int n) {
        static const int maxn = 1690, maxp = 3, pr[maxp] = {2, 3, 5};
        static int tot = 1, seq[maxn + 1] = {1}, idx[maxp] = {};
        while(tot < n) {
            int nxt = INT_MAX;
            for(int i = 0; i < maxp; ++i)
                nxt = min(nxt, seq[idx[i]] * pr[i]);
            seq[tot++] = nxt;
            for(int i = 0; i < maxp; ++i)
                idx[i] += seq[idx[i]] * pr[i] == nxt;
        }
        return seq[n - 1];
    }
};
