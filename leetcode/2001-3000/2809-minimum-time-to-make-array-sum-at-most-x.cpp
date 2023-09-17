class Solution {
public:
    int minimumTime(vector<int>& A, vector<int>& B, int upp) {
        int n = A.size(), s = 0, d = 0;
        for(int x: A)
            s += x;
        for(int x: B)
            d += x;
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return B[u] < B[v];
        });
        static const int INF = 0x3f3f3f3f;
        vector<int> dp = {0};
        for(int i: ord) {
            dp.push_back(-INF);
            for(int j = dp.size() - 1; j > 0; --j)
                dp[j] = max(dp[j], dp[j - 1] + A[i] + j * B[i]);
        }
        for(int i = 0; i <= n; ++i, s += d)
            if(s - dp[i] <= upp)
                return i;
        return -1;
    }
};
