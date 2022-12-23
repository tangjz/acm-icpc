class Solution {
public:
    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
        int n = vals.size();
        vector<vector<int> > e(n);
        auto addEdge = [&](int u, int v) {
            if(vals[v] > 0)
                e[u].push_back(vals[v]);
        };
        for(auto &it: edges) {
            addEdge(it[0], it[1]);
            addEdge(it[1], it[0]);
        }
        int ans = vals[0];
        for(int i = 0; i < n; ++i) {
            int tmp = vals[i];
            sort(e[i].begin(), e[i].end(), greater<int>());
            if(e[i].size() > k)
                e[i].resize(k);
            for(int x: e[i])
                tmp += x;
            ans = max(ans, tmp);
        }
        return ans;
    }
};
