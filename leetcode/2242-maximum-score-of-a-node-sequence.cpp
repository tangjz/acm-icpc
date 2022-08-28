class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        int n = scores.size();
        vector<vector<int> > adj(n, vector<int>(3, -1));
        auto upd = [&](vector<int> &ret, int u) {
            for(int i = 0; i < 3; ++i) {
                if(ret[i] == u)
                    break;
                if(ret[i] == -1 || scores[ret[i]] < scores[u])
                    swap(ret[i], u);
            }
        };
        for(auto &it: edges) {
            upd(adj[it[0]], it[1]);
            upd(adj[it[1]], it[0]);
        }
        int ans = -1;
        for(auto &it: edges) {
            int a, b = it[0], c = it[1], d;
            for(int i = 0; i < 3; ++i) {
                if(adj[b][i] == -1)
                    break;
                a = adj[b][i];
                if(a == c)
                    continue;
                for(int j = 0; j < 3; ++j) {
                    if(adj[c][j] == -1)
                        break;
                    d = adj[c][j];
                    if(a == d || b == d)
                        continue;
                    // printf("%d %d %d %d: %d\n", a, b, c, d, scores[a] + scores[b] + scores[c] + scores[d]);
                    ans = max(ans, scores[a] + scores[b] + scores[c] + scores[d]);
                }
            }
        }
        return ans;
    }
};
