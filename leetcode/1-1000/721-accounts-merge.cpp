class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        unordered_map<string, int> Hash;
        vector<int> dsu(n, -1);
        vector<vector<string> > emails(n);
        auto get_id = [&](string &s) -> int {
            auto it = Hash.find(s);
            if(it != Hash.end())
                return it -> second;
            int idx = dsu.size();
            dsu.push_back(-1);
            emails.push_back({});
            emails.back().push_back(s);
            return Hash[s] = idx;
        };
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) -> bool {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return 0;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
            emails[v].insert(emails[v].end(), emails[u].begin(), emails[u].end());
            vector<string>().swap(emails[u]);
            return 1;
        };
        vector<vector<int> > bel(n);
        for(int i = 0; i < n; ++i) {
            int m = accounts[i].size();
            // bel[i].push_back(i);
            for(int j = 1; j < m; ++j) {
                bel[i].push_back(get_id(accounts[i][j]));
                dsu_merge(i, bel[i].back());
            }
        }
        vector<vector<string> > ret;
        for(int i = 0; i < n; ++i) {
            for(int x: bel[i]) {
                if(emails[x].empty())
                    continue;
                emails[i].insert(emails[i].end(), emails[x].begin(), emails[x].end());
                vector<string>().swap(emails[x]);
            }
            if(emails[i].empty())
                continue;
            ret.push_back({accounts[i][0]});
            sort(emails[i].begin(), emails[i].end());
            ret.back().insert(ret.back().end(), emails[i].begin(), emails[i].end());
        }
        return ret;
    }
};
