class Solution {
public:
    int maximumRobots(vector<int>& A, vector<int>& B, long long C) {
        typedef long long LL;
        int n = A.size();
        vector<int> Log(n + 1);
        Log[0] = -1;
        for(int i = 1; i <= n; ++i)
            Log[i] = Log[i >> 1] + 1;
        int m = Log[n];
        vector<LL> psum = {0};
        vector<vector<int> > st(m + 1, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            psum.push_back(psum.back() + B[i]);
            st[0][i] = A[i];
        }
        for(int i = 1; i <= m; ++i)
            for(int j = 0; j <= n - (1 << i); ++j)
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            int L = 0, R = i + 1;
            while(L < R) {
                int M = (L + R + 1) >> 1;
                int j = i - M + 1, d = Log[M];
                LL cost = max(st[d][j], st[d][i - (1 << d) + 1]) + M * (psum[i + 1] - psum[j]);
                if(cost <= C) {
                    L = M;
                } else {
                    R = M - 1;
                }
            }
            ans = max(ans, L);
        }
        return ans;
    }
};
