class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& arr) {
        const int INF = 0x3f3f3f3f;
        int n = (int)arr.size();
        pair<int, int> f[2], g[2];
        f[0] = f[1] = {0, -1};
        for(int i = 0; i < n; ++i) {
            g[0] = g[1] = {INF, -1};
            for(int j = 0; j < n; ++j) {
                int k = f[0].second == j;
                pair<int, int> tmp = {f[k].first + arr[i][j], j};
                if(g[0] > tmp)
                    swap(g[0], tmp);
                if(g[1] > tmp)
                    swap(g[1], tmp);
            }
            f[0] = g[0];
            f[1] = g[1];
        }
        return f[0].first;
    }
};
