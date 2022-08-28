class Solution {
public:
    vector<string> trulyMostPopular(vector<string>& names, vector<string>& synonyms) {
        unordered_map<string, int> Hash;
        vector<int> dsu, ctr;
        vector<string> name;
        auto get_idx = [&](string const &s) {
            auto ret = Hash.insert({s, (int)Hash.size()});
            if(ret.second) {
                dsu.push_back(-1);
                ctr.push_back(0);
                name.push_back(s);
            }
            return ret.first -> second;
        };
        function<int(int)> dsu_find = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            name[v] = min(name[u], name[v]);
            ctr[v] += ctr[u];
        };
        for(auto &it: names) {
            auto pos = it.rfind('(');
            int u = get_idx(it.substr(0, pos));
            ctr[u] += stoi(it.substr(pos + 1, it.size() - pos - 2));
        }
        for(auto &it: synonyms) {
            auto pos = it.find(',');
            int u = get_idx(it.substr(1, pos - 1));
            int v = get_idx(it.substr(pos + 1, it.size() - pos - 2));
            dsu_merge(u, v);
        }
        vector<string> ret;
        for(int i = 0; i < (int)dsu.size(); ++i)
            if(dsu_find(i) == i)
                ret.push_back(name[i] + "(" + to_string(ctr[i]) + ")");
        return ret;
    }
};
