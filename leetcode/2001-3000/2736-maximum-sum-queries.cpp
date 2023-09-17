class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& x, vector<int>& y, vector<vector<int>>& que) {
        int n = x.size(), m = que.size();
        vector<int> ans(m, -1), ordX(n), ordQ(m), seqY = y;
        iota(ordX.begin(), ordX.end(), 0);
        sort(ordX.begin(), ordX.end(), [&](int const &u, int const &v) {
            return x[u] > x[v];
        });
        iota(ordQ.begin(), ordQ.end(), 0);
        sort(ordQ.begin(), ordQ.end(), [&](int const &u, int const &v) {
            return que[u][0] > que[v][0];
        });
        sort(seqY.begin(), seqY.end());
        seqY.erase(unique(seqY.begin(), seqY.end()), seqY.end());
        int sz = seqY.size();
        vector<int> bits(sz + 1, -1);
        for(int i = 0, j = 0; i < m; ++i) {
            for( ; j < n && x[ordX[j]] >= que[ordQ[i]][0]; ++j) {
                int o = lower_bound(seqY.begin(), seqY.end(), y[ordX[j]]) - seqY.begin() + 1;
                int v = x[ordX[j]] + y[ordX[j]];
                for( ; o > 0; o -= o & -o)
                    bits[o] = max(bits[o], v);
            }
            int o = lower_bound(seqY.begin(), seqY.end(), que[ordQ[i]][1]) - seqY.begin() + 1;
            int &v = ans[ordQ[i]];
            for( ; o <= sz; o += o & -o)
                v = max(v, bits[o]);
        }
        return ans;
    }
};
