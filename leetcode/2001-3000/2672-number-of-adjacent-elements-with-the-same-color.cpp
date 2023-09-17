class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& que) {
        int m = que.size(), ans = 0;
        vector<int> col(n), ret(m);
        for(int i = 0; i < m; ++i) {
            int u = que[i][0], c = que[i][1];
            if(col[u]) {
                ans -= u > 0 && col[u - 1] == col[u];
                ans -= u + 1 < n && col[u] == col[u + 1];
            }
            col[u] = c;
            ans += u > 0 && col[u - 1] == col[u];
            ans += u + 1 < n && col[u] == col[u + 1];
            ret[i] = ans;
        }
        return ret;
    }
};
