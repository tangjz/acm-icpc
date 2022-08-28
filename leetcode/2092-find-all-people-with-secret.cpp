class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        map<int, vector<vector<int> > > graph;
        graph[0].push_back({0, firstPerson});
        for(auto &it: meetings) {
            graph[it[2]].push_back({it[0], it[1]});
        }
        vector<bool> vis(n);
        vis[0] = 1;
        for(auto &state: graph) {
            map<int, vector<int> > e;
            for(auto &it: state.second) {
                e[it[0]].push_back(it[1]);
                e[it[1]].push_back(it[0]);
            }
            queue<int> que;
            for(auto &it: e) {
                if(vis[it.first])
                    que.push(it.first);
            }
            while(!que.empty()) {
                int u = que.front();
                que.pop();
                for(int v: e[u])
                    if(!vis[v]) {
                        vis[v] = 1;
                        que.push(v);
                    }
            }
        }
        vector<int> ret;
        for(int i = 0; i < n; ++i)
            if(vis[i])
                ret.push_back(i);
        return ret;
    }
};
