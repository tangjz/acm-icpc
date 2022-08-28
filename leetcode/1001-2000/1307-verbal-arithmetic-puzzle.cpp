class Solution {
    static const int maxd = 10, maxc = 26;
    int vis[maxc + 1], coe[maxc + 1];
    int n, pos[maxd + 1], pL[maxd + 3], pR[maxd + 3];
    bool dfs(int dep, int val) {
        if(dep == n)
            return !val;
        int idx = pos[dep], prd = coe[idx], sta = pR[0];
        if(sta == 1 && (vis[idx] & 2))
            sta = pR[sta];
        for( ; sta <= maxd; sta = pR[sta]) {
            pL[pR[sta]] = pL[sta];
            pR[pL[sta]] = pR[sta];
            if(dfs(dep + 1, val + prd * (sta - 1)))
                return 1;
            pL[pR[sta]] = pR[pL[sta]] = sta;
        }
        return 0;
    }
public:
    bool isSolvable(vector<string>& words, string result) {
        memset(vis, 0, sizeof vis);
        memset(coe, 0, sizeof coe);
        for(auto &it : words) {
            int len = (int)it.size();
            if(len > 1)
                vis[(int)(it[0] - 'A')] |= 2;
            for(int i = len - 1, pw = 1; i >= 0; --i, pw *= 10) {
                int o = (int)(it[i] - 'A');
                vis[o] |= 1;
                coe[o] += pw;
            }
        }
        {
            auto &it = result;
            int len = (int)it.size();
            if(len > 1)
                vis[(int)(it[0] - 'A')] |= 2;
            for(int i = len - 1, pw = 1; i >= 0; --i, pw *= 10) {
                int o = (int)(it[i] - 'A');
                vis[o] |= 1;
                coe[o] -= pw;
            }
        }
        n = 0;
        for(int i = 0; i < maxc; ++i)
            if(vis[i])
                pos[n++] = i;
        pR[0] = 1;
        for(int i = 1; i <= maxd; ++i) {
            pL[i] = i - 1;
            pR[i] = i + 1;
        }
        pL[maxd + 1] = maxd;
        return dfs(0, 0);
    }
};
