class Solution {
public:
    int maximumDetonation(vector<vector<int>>& cir) {
        typedef long long LL;
        int n = cir.size();
        vector<vector<int> > e(n);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == j) {
                    continue;
                }
                int dx = cir[i][0] - cir[j][0];
                int dy = cir[i][1] - cir[j][1];
                if((LL)dx * dx + (LL)dy * dy <= (LL)cir[i][2] * cir[i][2]) {
                    e[i].push_back(j);
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            int ctr = 0;
            queue<int> que;
            vector<bool> vis(n);
            auto upd = [&](int u) {
                if(vis[u])
                    return;
                que.push(u);
                vis[u] = 1;
                ++ctr;
            };
            upd(i);
            while(!que.empty()) {
                int u = que.front();
                que.pop();
                for(int v: e[u]) {
                    upd(v);
                }
            }
            ans = max(ans, ctr);
        }
        return ans;
    }
};
