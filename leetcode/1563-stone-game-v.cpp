class Solution {
    void upd_max(int &x, int y) {
        x < y && (x = y);
    }
public:
    int stoneGameV(vector<int>& w) {
        const int maxn = 501;
        int n = (int)w.size();
        static int s[maxn], dp[maxn][maxn];
        s[0] = 0;
        for(int i = 0; i < n; ++i) {
            memset(dp[i] + i, -1, (n - i) * sizeof(int));
            dp[i][i] = 0;
            s[i + 1] = s[i] + w[i];
        }
        function<int(int, int)> F = [&](int i, int j) {
            int &ret = dp[i][j];
            if(ret < 0) {
                for(int k = i; k < j; ++k) {
                    int lft = s[k + 1] - s[i], rht = s[j + 1] - s[k + 1];
                    if(lft <= rht)
                        upd_max(ret, F(i, k) + lft);
                    if(lft >= rht)
                        upd_max(ret, F(k + 1, j) + rht);
                }
            }
            return ret;
        };
        return F(0, n - 1);
    }
};
