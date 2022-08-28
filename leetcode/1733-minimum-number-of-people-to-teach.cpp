class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int m = languages.size();
        vector<vector<int> > vis(m, vector<int>(n));
        for(int i = 0; i < m; ++i)
            for(auto &j: languages[i])
                vis[i][j - 1] = 1;
        vector<int> sp(m);
        for(auto &it: friendships) {
            int u = it[0] - 1, v = it[1] - 1;
            bool skip = false;
            for(int i = 0; !skip && i < n; ++i)
                skip |= vis[u][i] && vis[v][i];
            if(!skip) {
                sp[u] = sp[v] = 1;
            }
        }
        int ans = m;
        for(int i = 0; i < n; ++i) {
            int cnt = 0;
            for(int j = 0; j < m; ++j)
                cnt += sp[j] && !vis[j][i];
            ans = min(ans, cnt);
        }
        return ans;
    }
};
