class Solution {
public:
    int minBuildTime(vector<int>& blocks, int split) {
        const int INF = 0x3f3f3f3f;
        int n = blocks.size();
        sort(blocks.begin(), blocks.end());
        vector<vector<int> > f(n + 1, vector<int>(n + 1, INF));
        f[0][0] = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = i; j >= 1; --j) {
                f[i][j] = max(f[i - 1][j - 1], blocks[i - 1]);
                int k = min(j + j, i);
                if(j < k)
                    f[i][j] = min(f[i][j], f[i][k] + split);
            }
            f[i][0] = INF;
        }
        return f[n][1];
    }
};
