class Solution {
public:
    int movingCount(int r, int c, int lim) {
        int n = r * c, m = max(r, c), ans = 0;
        vector<int> digits(m + 1);
        for(int i = 1; i <= m; ++i)
            digits[i] = digits[i / 10] + (i % 10);
        queue<int> que;
        vector<bool> vis(n);
        vis[0] = 1;
        que.push(0);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            ++ans;
            int ux = u / c, uy = u % c;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy, v = u + dx * c + dy;
                    if(vx < 0 || vx >= r || vy < 0 || vy >= c || vis[v])
                        continue;
                    vis[v] = 1;
                    if(digits[vx] + digits[vy] <= lim)
                        que.push(v);
                }
        }
        return ans;
    }
};
