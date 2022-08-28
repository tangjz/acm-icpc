class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& seq, vector<vector<int>>& edges, int sta, int dist) {
        const int INF = INT_MAX;
        int n = (int)edges.size();
        unordered_map<string, int> ctr;
        vector<int> dis(n, INF);
        queue<int> que;
        auto append = [&](int u, int dist) {
            if(dis[u] < INF)
                return;
            dis[u] = dist;
            que.push(u);
        };
        append(sta, 0);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            if(dis[u] == dist) {
                for(string &buf : seq[u])
                    ++ctr[buf];
            } else {
                int nxt = dis[u] + 1;
                for(int v : edges[u])
                    append(v, nxt);
            }
        }
        vector<pair<int, string> > toSort;
        for(auto &it : ctr)
            toSort.push_back({it.second, it.first});
        sort(toSort.begin(), toSort.end());
        vector<string> ret;
        for(auto &it : toSort)
            ret.push_back(it.second);
        return ret;
    }
};
