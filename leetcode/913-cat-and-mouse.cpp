class Solution {
    int getID(int n, int u, int v, int c) {
        return (u * n + v) << 1 | (c - 1);
    }
    void setID(int n, int id, int &u, int &v, int &c) {
        c = (id & 1) + 1;
        v = (id >> 1) % n;
        u = (id >> 1) / n;
    }
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = (int)graph.size(), m = n * n * 2;
        vector<pair<int, int> > state(m);
        queue<int> que;
        for(int i = 0; i < n; ++i)
            sort(graph[i].begin(), graph[i].end());
        for(int i = 0; i < m; ++i) {
            int u, v, c;
            setID(n, i, u, v, c);
            if(v == 0)
                continue;
            auto &it = state[i];
            if(u == 0) {
                it.first = 1;
            } else if(u == v) {
                it.first = 2;
            } else {
                it.first = 0;
            }
            if(it.first != 0) {
                que.push(i);
            } else {
                if(c == 1) {
                    it.second = (int)graph[u].size();
                } else {
                    it.second = (int)graph[v].size();
                    if(!graph[v].empty() && !graph[v].front())
                        --it.second;
                }
            }
        }
        int sta = getID(n, 1, 2, 1);
        while(!state[sta].first && !que.empty()) {
            int i = que.front(), u, v, c;
            que.pop();
            setID(n, i, u, v, c);
            auto &it = state[i];
            if(c == 2) {
                for(int p : graph[u]) {
                    int j = getID(n, p, v, 1);
                    auto &jt = state[j];
                    if(jt.first != 0)
                        continue;
                    if(it.first == 1) {
                        jt.first = 1;
                    } else if(!(--jt.second)) {
                        jt.first = 2;
                    }
                    if(jt.first != 0)
                        que.push(j);
                }
            } else {
                for(int p : graph[v]) {
                    int j = getID(n, u, p, 2);
                    auto &jt = state[j];
                    if(jt.first != 0)
                        continue;
                    if(it.first == 2) {
                        jt.first = 2;
                    } else if(!(--jt.second)) {
                        jt.first = 1;
                    }
                    if(jt.first != 0)
                        que.push(j);
                }
            }
        }
        return state[sta].first;
    }
};
