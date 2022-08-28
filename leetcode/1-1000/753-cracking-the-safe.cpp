class Solution {
public:
    string crackSafe(int n, int k) {
        // each pswd is an edge of automata for pow(k, n - 1) nodes
        int pw = 1;
        for(int i = 0; i < n; ++i)
            pw *= k;
        vector<bool> vis(pw);
        string s = ""; // reversed rep
        function<void(int)> dfs = [&](int u) {
            for(int i = 0, v = u * k % pw; i < k; ++i, ++v) {
                if(vis[v])
                    continue;
                vis[v] = 1;
                dfs(v);
                s += '0' + i;
            }
        };
        vis[0] = 1;
        dfs(0);
        for(int i = 0; i < n; ++i)
            s += '0';
        return s;
    }
};
