class Solution {
public:
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        int n = charge.size();
        vector<vector<pair<int, int> > > e(n);
        for(auto &it: paths) {
            e[it[0]].push_back({it[1], it[2]});
            e[it[1]].push_back({it[0], it[2]});
        }
        map<pair<int, int>, int> dis;
        set<pair<int, int> > vis;
        priority_queue<pair<int, pair<int, int> > > que;
        auto upd = [&](pair<int, int> u, int dist) {
            auto it = dis.find(u);
            if(it == dis.end() || dist < it -> second) {
                dis[u] = dist;
                que.push({-dist, u});
            }
        };
        upd({start, 0}, 0);
        while(!que.empty()) {
            pair<int, int> u = que.top().second, v;
            que.pop();
            if(!vis.insert(u).second)
                continue;
            int dist = dis[u];
            if(u.first == end)
                return dist;
            if(u.second < cnt)
                upd({u.first, u.second + 1}, dist + charge[u.first]);
            for(auto &it: e[u.first])
                if(it.second <= u.second)
                    upd({it.first, u.second - it.second}, dist + it.second);
        }
        return -1;
    }
};
