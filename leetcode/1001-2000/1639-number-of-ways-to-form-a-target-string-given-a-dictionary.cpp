class Solution {
public:
    int numWays(vector<string>& words, string target) {
        const int mod = (int)1e9 + 7, maxd = 26;
        int n = words[0].size(), m = target.size();
        vector<vector<int> > ctr(n, vector<int>(maxd));
        for(auto &it: words)
            for(int i = 0; i < n; ++i)
                ++ctr[i][(int)(it[i] - 'a')];
        vector<int> f(n + 1);
        f[0] = 1;
        for(char ch: target) {
            int x = ch - 'a';
            vector<int> g(n + 1);
            int pre = 0;
            for(int j = 0; j < n; ++j) {
                (pre += f[j]) >= mod && (pre -= mod);
                if(ctr[j][x])
                    g[j + 1] = 1LL * ctr[j][x] * pre % mod;
            }
            f = move(g);
        }
        int ans = 0;
        for(int x: f)
            (ans += x) >= mod && (ans -= mod);
        return ans;
    }
};
