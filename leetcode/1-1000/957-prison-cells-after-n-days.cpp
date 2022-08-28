class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        const int maxd = 8, maxs = 1 << 8 | 1;
        vector<int> que = {0}, vis(maxs, -1);
        for(int i = maxd - 1; i >= 0; --i)
            que[0] = que[0] << 1 | cells[i];
        vis[que[0]] = 0;
        int ans = -1;
        for(int i = 1; i <= n; ++i) {
            int msk = 0, pre = que[i - 1];
            for(int j = maxd - 1; j >= 0; --j) {
                bool same = (j > 0 ? (pre >> (j - 1)) & 1 : -1) == (j + 1 < maxd ? (pre >> (j + 1)) & 1 : -2);
                msk = msk << 1 | same;
            }
            if(vis[msk] != -1) {
                int sta = vis[msk], len = i - sta;
                ans = que[sta + (n - sta) % len];
                break;
            }
            que.push_back(msk);
            vis[msk] = i;
        }
        if(ans == -1)
            ans = que[n];
        for(int i = 0; i < maxd; ++i, ans >>= 1)
            cells[i] = ans & 1;
        return cells;
    }
};
