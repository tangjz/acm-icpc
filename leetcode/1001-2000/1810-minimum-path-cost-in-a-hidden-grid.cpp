/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     int move(char direction);
 *     boolean isTarget();
 * };
 */

class Solution {
    static constexpr int maxd = 4, dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
    static constexpr char *pat = "UDLR";
    static constexpr pair<int, int> INF = {INT_MAX, INT_MAX};
    void dfs(pair<int, int> s, pair<int, int> &t, map<pair<int, int>, vector<int> > &msk, GridMaster &api) {
        if(msk.count(s))
            return;
        msk[s].assign(4, -1);
        if(api.isTarget())
            t = s;
        for(int i = 0; i < 4; ++i) {
            if(!api.canMove(pat[i]))
                continue;
            msk[s][i] = api.move(pat[i]);
            dfs({s.first + dx[i], s.second + dy[i]}, t, msk, api);
            api.move(pat[i ^ 1]);
        }
    }
public:
    int findShortestPath(GridMaster &master) {
        pair<int, int> s = {0, 0}, t = INF;
        map<pair<int, int>, vector<int> > msk;
        dfs(s, t, msk, master);
        if(t == INF)
            return -1;
        map<pair<int, int>, int> dis;
        set<pair<int, int> > vis;
        priority_queue<pair<int, pair<int, int> > > que;
        auto upd = [&](pair<int, int> s, int d) {
            if(!msk.count(s))
                return;
            if(dis.count(s) && dis[s] <= d)
                return;
            dis[s] = d;
            que.push({-d, s});
        };
        upd(s, 0);
        while(!que.empty()) {
            pair<int, int> u = que.top().second;
            que.pop();
            if(!vis.insert(u).second)
                continue;
            int d = dis[u];
            if(u == t)
                return d;
            vector<int> &vec = msk[u];
            for(int i = 0; i < 4; ++i)
                if(vec[i] != -1)
                    upd({u.first + dx[i], u.second + dy[i]}, d + vec[i]);
        }
        return -1;
    }
};
