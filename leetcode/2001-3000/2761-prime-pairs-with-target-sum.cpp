class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {
        static const int maxn = (int)1e6 + 1;
        static int ptot = 0, pr[maxn], d[maxn] = {};
        if(!ptot) {
            for(int i = 2; i < maxn; ++i) {
                if(!d[i])
                    pr[ptot++] = d[i] = i;
                for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
                    d[k] = pr[j];
                    if(d[i] == pr[j])
                        break;
                }
            }
            pr[ptot] = maxn;
        }
        int m = lower_bound(pr, pr + ptot + 1, n) - pr;
        vector<vector<int> > ret;
        for(int i = 0, j = m - 1; i <= j; ++i) {
            for( ; i <= j && pr[i] + pr[j] > n; --j);
            if(i <= j && pr[i] + pr[j] == n)
                ret.push_back({pr[i], pr[j]});
        }
        return ret;
    }
};
