class Solution {
public:
    vector<int> lightSticks(int height, int width, vector<int>& indices) {
        int r = height + 1, c = width + 1, n = r * c;
        vector<bool> vis(n + n);
        for(int x: indices)
            vis[x] = 1;
        vector<vector<int> > e(n);
        for(int i = 0, idx = 0; i < r; ++i) {
            if(i > 0)
                for(int j = 0; j < c; ++j, ++idx) {
                    if(vis[idx])
                        continue;
                    int u = i * c + j, v = u - c;
                    e[u].push_back(v);
                    e[v].push_back(u);
                }
            for(int j = 1; j < c; ++j, ++idx) {
                if(vis[idx])
                    continue;
                int u = i * c + j, v = u - 1;
                e[u].push_back(v);
                e[v].push_back(u);
            }
        }
        int ans = INT_MAX, upp = 0;
        for(int i = 0; i < n; ++i)
            upp += !e[i].empty();
        vector<int> cand, dis(n);
        queue<int> que;
        for(int i = 0; i < n; ++i) {
            if(e[i].empty())
                continue;
            dis.assign(n, -1);
            int cnt = 0, las = dis[i] = 0;
            que.push(i);
            while(!que.empty()) {
                int u = que.front();
                que.pop();
                ++cnt;
                las = dis[u];
                for(int v: e[u])
                    if(dis[v] == -1) {
                        dis[v] = dis[u] + 1;
                        que.push(v);
                    }
            }
            // printf("%d %d %d %d\n", i, las, cnt, upp);
            if(cnt < upp)
                return {};
            if(las < ans) {
                ans = las;
                cand.clear();
            }
            if(las == ans)
                cand.push_back(i);
        }
        return cand;
    }
};
