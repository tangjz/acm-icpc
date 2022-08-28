class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        const int maxd = 26;
        vector<int> sp[maxd], idx(maxd);
        for(int i = 0; i < maxd; ++i) {
            sp[i] = {i};
            idx[i] = i;
        }
        for(auto &it: equations) {
            if(it[1] != '=')
                continue;
            int u = idx[it[0] - 'a'], v = idx[it[3] - 'a'];
            if(u == v)
                continue;
            for(int x: sp[v]) {
                sp[u].push_back(x);
                idx[x] = u;
            }
        }
        for(auto &it: equations) {
            if(it[1] == '=')
                continue;
            int u = idx[it[0] - 'a'], v = idx[it[3] - 'a'];
            if(u == v)
                return 0;
        }
        return 1;
    }
};
