class Solution {
public:
    bool checkContradictions(vector<vector<string>>& equations, vector<double>& values) {
        int m = values.size();
        unordered_map<string, int> Hash;
        vector<double> dis;
        vector<int> dsu;
        auto sgn = [&](double x) {
            static const double eps = 1e-9;
            return (x > eps) - (x < -eps);
        };
        auto getIdx = [&](string const &buf) {
            auto ret = Hash.insert({buf, Hash.size()});
            if(ret.second) {
                dsu.push_back(-1);
                dis.push_back(0);
            }
            return ret.first -> second;
        };
        function<int(int)> dsuFind = [&](int x) {
            if(dsu[x] < 0)
                return x;
            int t = dsu[x];
            dsu[x] = dsuFind(t);
            dis[x] += dis[t];
            return dsu[x];
        };
        auto dsuMerge = [&](int u, int v, double w) -> bool {
            int x = dsuFind(u), y = dsuFind(v);
            w = log(w);
            if(x == y)
                return !sgn(dis[u] - dis[v] - w);
            if(dsu[x] < dsu[y]) {
                swap(x, y);
                swap(u, v);
                w = -w;
            }
            dsu[y] -= dsu[x] == dsu[y];
            dsu[x] = y;
            dis[x] = dis[v] + w - dis[u];
            return 1;
        };
        for(int i = 0; i < m; ++i)
            if(!dsuMerge(getIdx(equations[i][0]), getIdx(equations[i][1]), values[i]))
                return 1;
        return 0;
    }
};
