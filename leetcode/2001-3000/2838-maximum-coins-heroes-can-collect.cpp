class Solution {
public:
    vector<long long> maximumCoins(vector<int>& A, vector<int>& B, vector<int>& C) {
        typedef long long LL;
        int n = A.size(), m = B.size();
        vector<int> oA(n), oB(m);
        iota(oA.begin(), oA.end(), 0);
        sort(oA.begin(), oA.end(), [&](int const &u, int const &v) {
            return A[u] < A[v];
        });
        iota(oB.begin(), oB.end(), 0);
        sort(oB.begin(), oB.end(), [&](int const &u, int const &v) {
            return B[u] < B[v];
        });
        LL sum = 0;
        vector<LL> ans(n);
        for(int i = 0, j = 0; i < n; ++i) {
            int u = oA[i];
            for( ; j < m && B[oB[j]] <= A[u]; sum += C[oB[j++]]);
            ans[u] = sum;
        }
        return ans;
    }
};