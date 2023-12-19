class Solution {
public:
    long long maxBalancedSubsequenceSum(vector<int>& A) {
        int n = A.size();
        vector<int> que(n);
        for(int i = 0; i < n; ++i)
            que[i] = A[i] - i;
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        typedef long long LL;
        LL ans = LLONG_MIN;
        vector<LL> bits(m + 1);
        for(int i = 0; i < n; ++i) {
            int u = lower_bound(que.begin(), que.end(), A[i] - i) - que.begin() + 1;
            LL v = 0;
            for(int x = u; x > 0; x -= x & -x)
                v = max(v, bits[x]);
            v += A[i];
            ans = max(ans, v);
            for(int x = u; x <= m; x += x & -x)
                bits[x] = max(bits[x], v);
        }
        return ans;
    }
};
