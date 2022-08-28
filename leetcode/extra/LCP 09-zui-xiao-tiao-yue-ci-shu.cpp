class Solution {
public:
    int minJump(vector<int>& jump) {
        int n = jump.size();
        vector<int> dis(n, -1), dsu(n, -1), rep(n);
        iota(rep.begin(), rep.end(), 0);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(dsu[u], dsu[v]);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            rep[v] = max(rep[u], rep[v]);
        };
        queue<int> que;
        dis[0] = 0;
        if(n > 1)
            dsu_merge(0, 1);
        que.push(0);
        while(!que.empty()) {
            int u = que.front(), v, nxt = dis[u] + 1;
            que.pop();
            v = u + jump[u];
            if(v >= n)
                return nxt;
            if(dis[v] == -1) {
                dis[v] = nxt;
                if(v + 1 < n)
                    dsu_merge(v, v + 1);
                que.push(v);
            }
            for(v = dsu_find(0); v < u; v = dsu_find(v)) {
                dis[v] = nxt;
                dsu_merge(v, v + 1);
                que.push(v);
            }
        }
        return 0;
    }
};
