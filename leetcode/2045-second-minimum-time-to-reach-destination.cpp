class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[--it[0]].push_back(--it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<int> dp(n << 1, -1);
        queue<int> que;
        auto upd = [&](int u, int x) {
            if(dp[u] != -1)
                return;
            dp[u] = x;
            que.push(u);
            // printf("%d: %d\n", u >> 1, x);
        };
        upd(0, 0);
        while(!que.empty()) {
            int uu = que.front(), u = uu >> 1, o = uu & 1;
            que.pop();
            for(int v: e[u]) {
                upd(v << 1 | !o, dp[uu] + 1);
            }
        }
        // for(int i = 0; i < n; ++i) {
        //     printf("%d: %d %d\n", i + 1, dp[i << 1], dp[i << 1 | 1]);
        // }
        vector<int> sol;
        for(int i = 0; i < 2; ++i) {
            if(dp[(n - 1) << 1 | i] == -1)
                continue;
            sol.push_back(dp[(n - 1) << 1 | i]);
            sol.push_back(dp[(n - 1) << 1 | i] + 2);
        }
        sort(sol.begin(), sol.end());
        // for(int x: sol)
        //     printf("sol %d\n", x);
        int pos = 1;
        while(sol[pos] == sol[0])
            ++pos;
        // printf("%d\n", pos);
        int ans = 0;
        // printf("%d\n", sol[pos]);
        for(int i = 0; i < sol[pos]; ++i) {
            ans += time;
            int mod = change << 1, rem = ans % mod;
            if(i + 1 < sol[pos] && rem >= change) {
                ans += mod - rem;
            }
        }
        return ans;
    }
};
