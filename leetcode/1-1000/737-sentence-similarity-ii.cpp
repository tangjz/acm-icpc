class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& A, vector<string>& B, vector<vector<string>>& P) {
        if(A.size() != B.size())
            return 0;
        unordered_map<string, int> Hash;
        vector<int> dsu;
        auto get_id = [&](string const &s) -> int {
            auto it = Hash.find(s);
            if(it != Hash.end())
                return it -> second;
            int tot = dsu.size();
            dsu.push_back(-1);
            Hash.insert({s, tot});
            return tot;
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
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            return 1;
        };
        for(auto &it: P)
            dsu_merge(get_id(it[0]), get_id(it[1]));
        int n = A.size();
        for(int i = 0; i < n; ++i)
            if(dsu_find(get_id(A[i])) != dsu_find(get_id(B[i])))
                return 0;
        return 1;
    }
};
