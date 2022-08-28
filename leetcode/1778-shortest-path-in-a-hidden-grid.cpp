/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     void move(char direction);
 *     boolean isTarget();
 * };
 */

class Solution {
    static constexpr int maxd = 4, dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
    static constexpr char *pat = "UDLR";
    static constexpr pair<int, int> INF = {INT_MAX, INT_MAX};
    void dfs(pair<int, int> s, pair<int, int> &t, map<pair<int, int>, int> &msk, GridMaster &api) {
        if(msk.count(s))
            return;
        msk[s] = 0;
        if(api.isTarget())
            t = s;
        for(int i = 0; i < 4; ++i) {
            if(!api.canMove(pat[i]))
                continue;
            msk[s] |= 1 << i;
            api.move(pat[i]);
            dfs({s.first + dx[i], s.second + dy[i]}, t, msk, api);
            api.move(pat[i ^ 1]);
        }
    }
public:
    int findShortestPath(GridMaster &master) {
        pair<int, int> s = {0, 0}, t = INF;
        map<pair<int, int>, int> msk;
        dfs(s, t, msk, master);
        if(t == INF)
            return -1;
        set<pair<int, int> > vis;
        queue<pair<pair<int, int>, int> > que;
        auto upd = [&](pair<int, int> s, int d) {
            if(!msk.count(s) || vis.count(s))
                return;
            vis.insert(s);
            que.push({s, d});
        };
        upd(s, 0);
        while(!que.empty()) {
            pair<int, int> u;
            int d;
            tie(u, d) = que.front();
            que.pop();
            if(u == t)
                return d;
            int mask = msk[u];
            for(int i = 0; i < 4; ++i)
                if((mask >> i) & 1)
                    upd({u.first + dx[i], u.second + dy[i]}, d + 1);
        }
        return -1;
    }
};
