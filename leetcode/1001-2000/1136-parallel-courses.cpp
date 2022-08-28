class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<int> deg(n);
        vector<vector<int> > e(n);
        for(auto &it: relations) {
            e[--it[0]].push_back(--it[1]);
            ++deg[it[1]];
        }
        vector<pair<int, int> > que;
        for(int i = 0; i < n; ++i)
            if(!deg[i])
                que.push_back({i, 1});
        for(int i = 0; i < n; ++i) {
            if(i == que.size())
                return -1;
            pair<int, int> cur = que[i];
            for(int v: e[cur.first])
                if(!(--deg[v]))
                    que.push_back({v, cur.second + 1});
        }
        return que.back().second;
    }
};
