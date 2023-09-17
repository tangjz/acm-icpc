class Solution {
public:
    long long maximumOr(vector<int>& A, int k) {
        typedef long long LL;
        int n = A.size();
        vector<int> pre(n), suf(n);
        for(int i = 1; i < n; ++i)
            pre[i] = pre[i - 1] | A[i - 1];
        for(int i = n - 2; i >= 0; --i)
            suf[i] = suf[i + 1] | A[i + 1];
        LL ans = 0;
        for(int i = 0; i < n; ++i)
            ans = max(ans, ((LL)A[i] << k) | pre[i] | suf[i]);
        return ans;
    }
};
