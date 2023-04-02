class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        vector<int> dis(n, -1), dsu(n + 2, -1);
        queue<int> que;
        for(int x: banned)
            dsu[x] = x + 2;
        function<int(int)> dsuFind = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        auto upd = [&](int x, int d) {
            if(dsu[x] != -1)
                return;
            dsu[x] = x + 2;
            dis[x] = d;
            que.push(x);
        };
        upd(p, 0);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            int L = max(u - k + 1, 0), R = min(u + k - 1, n - 1);
            L = L + L + k - 1 - u;
            R = R + R - k + 1 - u;
            for(int x = dsuFind(L); x <= R; x = dsuFind(x))
                upd(x, dis[u] + 1);
        }
        return dis;
    }
};
