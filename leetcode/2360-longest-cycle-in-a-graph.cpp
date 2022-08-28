class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int ans = -1, n = edges.size();
        vector<pair<int, int> > dis(n, {INT_MAX, -1});
        for(int i = 0; i < n; ++i) {
            if(dis[i].second != -1)
                continue;
            for(int u = i, d = 0; u != -1; u = edges[u], ++d) {
                if(dis[u].first != INT_MAX) {
                    if(dis[u].second == i)
                        ans = max(ans, d - dis[u].first);
                    break;
                }
                dis[u] = {d, i};
            }
        }
        return ans;
    }
};
