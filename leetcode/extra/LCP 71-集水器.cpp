class Solution {
public:
    int reservoir(vector<string>& shape) {
        const int INF = 0x3f3f3f3f;
        int r = shape.size(), c = shape[0].size(), n = r * c * 2;
        vector<vector<int> > e(n);
        vector<int> dis(n, INF), low(n, INF);
        priority_queue<pair<int, int> > que;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int pU = (i * c + j) << 1, pD = pU + 1, pL = pD, pR = pU;
                if(shape[i][j] == 'r')
                    swap(pL, pR);
                low[pU] = low[pD] = r - 1 - i;
                auto addEdge = [&](int u, int v) {
                    e[u].push_back(v);
                    e[v].push_back(u);
                };
                if(shape[i][j] == '.') {
                    addEdge(pU, pD);
                }
                if(i > 0) {
                    int qD = pU - (c << 1) + 1;
                    addEdge(pU, qD);
                } else {
                    dis[pU] = min(dis[pU], low[pU] + 1);
                }
                if(i == r - 1) {
                    dis[pD] = min(dis[pD], low[pD]);
                }
                if(j > 0) {
                    int qR = pU - 2 + (shape[i][j - 1] == 'r');
                    addEdge(pL, qR);
                } else {
                    dis[pL] = min(dis[pL], low[pL]);
                }
                if(j == c - 1) {
                    dis[pR] = min(dis[pR], low[pR]);
                }
                if(dis[pL] < INF)
                    que.push({-dis[pL], pL});
                if(dis[pR] < INF)
                    que.push({-dis[pR], pR});
            }
        while(!que.empty()) {
            pair<int, int> cur = que.top();
            que.pop();
            int u = cur.second;
            if(-cur.first != dis[u])
                continue;
            for(int v: e[u]) {
                int w = max(dis[u], low[v]);
                if(w < dis[v]) {
                    dis[v] = w;
                    que.push({-dis[v], v});
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans += dis[i] < INF && dis[i] > low[i];
        return ans;
    }
};
