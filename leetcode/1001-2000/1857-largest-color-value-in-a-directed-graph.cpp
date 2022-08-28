class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<int> deg(n);
        vector<vector<int> > e(n, vector<int>());
        for(auto &it: edges) {
            ++deg[it[1]];
            e[it[0]].push_back(it[1]);
        }
        vector<int> ord;
        for(int i = 0; i < n; ++i)
            if(!deg[i])
                ord.push_back(i);
        for(int i = 0; i < ord.size(); ++i) {
            int u = ord[i];
            for(int v: e[u])
                if(!(--deg[v]))
                    ord.push_back(v);
        }
        if(ord.size() < n)
            return -1;
        const int maxd = (int)26;
        int ans = 0;
        vector<vector<int> > dp(n, vector<int>(maxd));
        reverse(ord.begin(), ord.end());
        for(int u: ord) {
            for(int v: e[u]) {
                for(int i = 0; i < maxd; ++i)
                    dp[u][i] = max(dp[u][i], dp[v][i]);
            }
            ans = max(ans, ++dp[u][(int)(colors[u] - 'a')]);
        }
        return ans;
    }
};
