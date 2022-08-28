class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        typedef unsigned int UL;
        typedef unsigned long long ULL;
        unordered_set<ULL> sp;
        for(auto &it: points) {
            ULL msk = (ULL)it[0] << 32 | (UL)it[1];
            sp.insert(msk);
        }
        int n = 0;
        for(auto &msk: sp) {
            int x = msk >> 32, y = msk;
            points[n][0] = msk >> 32;
            points[n++][1] = msk;
        }
        points.resize(n);
        vector<int> px;
        px.reserve(n);
        for(auto &it: points)
            px.push_back(it[0]);
        int rht = n >> 1, lft = n - 1 - rht;
        nth_element(px.begin(), px.begin() + lft, px.end());
        nth_element(px.begin() + lft, px.begin() + rht, px.end());
        int mid = px[lft] + px[rht];
        unordered_map<ULL, int> ctr;
        for(auto &it: points) {
            int x2 = it[0] + it[0];
            if(x2 == mid)
                continue;
            if(x2 < mid) {
                ULL msk = (ULL)(mid - it[0]) << 32 | (ULL)it[1];
                ++ctr[msk];
            } else {
                ULL msk = (ULL)it[0] << 32 | (ULL)it[1];
                --ctr[msk];
            }
        }
        for(auto &it: ctr)
            if(it.second)
                return 0;
        return 1;
    }
};
