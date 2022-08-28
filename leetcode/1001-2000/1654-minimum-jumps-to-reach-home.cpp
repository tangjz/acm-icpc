class Solution {
public:
    int minimumJumps(vector<int>& obs, int a, int b, int x) {
        const int INF = 0x3f3f3f3f;
        int r = gcd(a, b);
        a /= r;
        b /= r;
        if(x % r > 0)
            return -1;
        int upp = (max(*max_element(obs.begin(), obs.end()), x) - 1) / r + 1 + a + b;
        x /= r;
        vector<bool> ban(upp + 1);
        for(int pos: obs)
            if(pos % r == 0)
                ban[pos / r] = 1;
        vector<vector<int> > dis(2, vector<int>(upp + 1, INF));
        queue<pair<int, int> > que;
        auto upd = [&](int typ, int pos, int d) {
            if(pos < 0 || pos > upp || ban[pos] || dis[typ][pos] != INF)
                return;
            dis[typ][pos] = d;
            que.push({typ, pos});
        };
        upd(0, 0, 0);
        while(!que.empty()) {
            int typ, pos;
            tie(typ, pos) = que.front();
            que.pop();
            upd(0, pos + a, dis[typ][pos] + 1);
            if(!typ)
                upd(1, pos - b, dis[typ][pos] + 1);
        }
        int ans = min(dis[0][x], dis[1][x]);
        return ans < INF ? ans : -1;
    }
};
