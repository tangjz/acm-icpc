class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& mp, vector<int>& seq) {
        int r = mp.size(), c = mp[0].size(), n = r * c;
        vector<int> dis(n, INT_MAX);
        priority_queue<pair<int, int> > que;
        auto upd = [&](int x, int d) {
            if(dis[x] > d) {
                dis[x] = d;
                que.push({-dis[x], x});
            }
        };
        upd(0, mp[0][0]);
        while(!que.empty()) {
            pair<int, int> cur = que.top();
            que.pop();
            int u = cur.second;
            if(dis[u] != -cur.first)
                continue;
            // printf("u %d: dis %d\n", u, dis[u]);
            int ux = u / c, uy = u % c;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy;
                    if(vx < 0 || vx >= r || vy < 0 || vy >= c)
                        continue;
                    upd(u + dx * c + dy, max(dis[u], mp[vx][vy]));
                }
        }
        sort(dis.begin(), dis.end());
        vector<int> ans;
        for(int x: seq) {
            int y = lower_bound(dis.begin(), dis.end(), x) - dis.begin();
            ans.push_back(y);
        }
        return ans;
    }
};
