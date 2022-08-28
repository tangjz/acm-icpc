class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, int> Hash;
        auto getID = [&](string &buf) {
            auto it = Hash.find(buf);
            if(it == Hash.end())
                it = Hash.insert({buf, (int)Hash.size()}).first;
            return it -> second;
        };
        for(auto &it: equations) {
            getID(it[0]);
            getID(it[1]);
        }
        for(auto &it: queries) {
            getID(it[0]);
            getID(it[1]);
        }
        int n = (int)Hash.size();
        vector<bool> vis(n);
        vector<int> dsu(n, -1);
        vector<double> dis(n, 0.0);
        function<int(int)> dsuFind = [&](int x) {
            if(dsu[x] < 0)
                return x;
            int t = dsu[x];
            dsu[x] = dsuFind(t);
            dis[x] += dis[t];
            return dsu[x];
        };
        auto dsuMerge = [&](int u, int v, double w) {
            int x = dsuFind(u), y = dsuFind(v);
            if(x == y)
                return;
            w = log(w) - dis[u] + dis[v];
            if(dsu[x] < dsu[y]) {
                swap(x, y);
                w = -w;
            }
            dsu[y] -= dsu[x] == dsu[y];
            dsu[x] = y;
            dis[x] = w;
        };
        auto dsuDist = [&](int u, int v) {
            int x = dsuFind(u), y = dsuFind(v);
            if(x != y)
                return -1.0;
            return exp(dis[u] - dis[v]);
        };
        auto jt = values.begin();
        for(auto &it: equations) {
            int u = getID(it[0]);
            int v = getID(it[1]);
            vis[u] = vis[v] = 1;
            dsuMerge(u, v, *(jt++));
        }
        vector<double> ret;
        for(auto &it: queries) {
            int u = getID(it[0]);
            int v = getID(it[1]);
            ret.push_back(vis[u] && vis[v] ? dsuDist(u, v) : -1);
        }
        return ret;
    }
};
