class Solution {
public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& que) {
        int n = s.size(), m = que.size();
        vector<vector<int> > pos;
        for(int i = 0; i < m; ++i) {
            auto &it = que[i];
            int len = 1;
            it[0] ^= it[1];
            for( ; (1 << len) <= it[0]; ++len);
            if(pos.size() <= len)
                pos.resize(len + 1);
            pos[len].push_back(i);
        }
        int mx = pos.size();
        vector<vector<int> > ans(m);
        for(int i = 1; i < mx; ++i) {
            if(pos[i].empty())
                continue;
            static unordered_map<int, int> Hash;
            Hash.clear();
            for(int j = 0, h = 0, msk = (1 << i) - 1; j < n; ++j) {
                int o = s[j] - '0';
                h = (h << 1 | o) & msk;
                if(j >= i - 1)
                    Hash.insert({h, j});
            }
            for(int j: pos[i]) {
                int val = que[j][0];
                auto it = Hash.find(val);
                if(it == Hash.end()) {
                    ans[j] = {-1, -1};
                } else {
                    ans[j] = {it -> second - i + 1, it -> second};
                }
            }
        }
        return ans;
    }
};
