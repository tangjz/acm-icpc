class Solution {
public:
    int extractMantra(vector<string>& mat, string seq) {
        const int INF = 0x3f3f3f3f;
        int r = mat.size(), c = mat[0].size(), n = seq.size(), m = r * c * n, ans = INF;
        vector<int> dis(m, INF);
        queue<int> que;
        auto upd = [&](int x, int y, int i, int d) {
            if(x < 0 || x >= r || y < 0 || y >= c)
                return;
            if(i == n) {
                assert(ans >= d);
                ans = d;
                // ans = min(ans, d);
                return;
            }
            int k = (x * c + y) * n + i;
            if(dis[k] != INF)
                return;
            dis[k] = d;
            que.push(k);
        };
        upd(0, 0, 0, 0);
        while(!que.empty() && ans == INF) {
            int k = que.front(), d = dis[k];
            que.pop();
            int i = k % n, y = (k /= n) % c, x = (k /= c);
            if(mat[x][y] == seq[i])
                upd(x, y, i + 1, d + 1);
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(x + dx, y + dy, i, d + 1);
                }
        }
        return ans < INF ? ans : -1;
    }
};
