class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& A) {
        int n = A.size();
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<int> ord = {0}, par(n), seq = {bob}, dp(n, INT_MIN);
        par[0] = -1;
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u])
                if(v != par[u]) {
                    par[v] = u;
                    ord.push_back(v);
                }
        }
        while(seq.back() != 0)
            seq.push_back(par[seq.back()]);
        for(int i = 0, j = seq.size() - 1; i <= j; ++i, --j)
            if(i == j) {
                A[seq[i]] /= 2;
            } else {
                A[seq[i]] = 0;
            }
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i];
            if(dp[u] == INT_MIN) {
                dp[u] = 0;
            }
            dp[u] += A[u];
            if(par[u] != -1)
                dp[par[u]] = max(dp[par[u]], dp[u]);
        }
        return dp[0];
    }
};
