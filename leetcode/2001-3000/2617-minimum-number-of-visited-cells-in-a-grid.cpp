class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<int> dsuR(n + 1, -1), dsuC(n + 1, -1);
        function<int(vector<int>&, int)> dsuFind = [&](vector<int> &dsu, int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu, dsu[x]));
        };
        vector<int> dis(n, -1);
        queue<int> que;
        auto upd = [&](int x, int d) {
            if(dis[x] != -1)
                return;
            dis[x] = d;
            que.push(x);
        };
        upd(0, 1);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            int ux = u / c, uy = u % c, adt = grid[ux][uy];
            for(int vLim = min(ux + adt, r - 1) * c + uy, v = dsuFind(dsuR, u); v <= vLim; v = dsuFind(dsuR, v)) {
                dsuR[v] = min(v + c, n);
                upd(v, dis[u] + 1);
            }
            for(int vLim = ux * c + min(uy + adt, c - 1), v = dsuFind(dsuC, u); v <= vLim; v = dsuFind(dsuC, v)) {
                dsuC[v] = min(v + 1, n);
                upd(v, dis[u] + 1);
            }
        }
        return dis[n - 1];
    }
};
