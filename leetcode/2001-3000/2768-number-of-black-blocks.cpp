class Solution {
public:
    vector<long long> countBlackBlocks(int r, int c, vector<vector<int>>& a) {
        typedef long long LL;
        unordered_set<LL> sp;
        for(auto &it: a)
            sp.insert((LL)it[0] * c + it[1]);
        vector<LL> ans(5);
        ans[0] = (r - 1LL) * (c - 1LL);
        for(int i = 1; i < (1 << 4); ++i) {
            int sz = 0, las = -1;
            for(int j = 0; j < 4; ++j)
                if((i >> j) & 1) {
                    ++sz;
                    las = j;
                }
            for(auto &it: a) {
                int x = it[0] - (las >> 1), y = it[1] - (las & 1);
                if(x < 0 || x + 1 >= r || y < 0 || y + 1 >= c)
                    continue;
                bool skp = 0;
                for(int j = 0; !skp && j < 4; ++j) {
                    LL key = ((LL)(x + (j >> 1)) * c + (y + (j & 1)));
                    skp |= sp.count(key) != ((i >> j) & 1);
                }
                ans[sz] += !skp;
            }
        }
        for(int i = 1; i <= 4; ++i)
            ans[0] -= ans[i];
        return ans;
    }
};
