class Solution {
    bool reduce(vector<int> &sums, int &u) {
        // assert(u >= 0);
        int sz = sums.size();
        vector<bool> vis(sz);
        vector<int> ret;
        bool hasZero = 0;
        for(int i = 0, j = 0; i < sz; ++i) {
            if(vis[i])
                continue;
            vis[i] = 1;
            for( ; j < sz && (vis[j] || sums[j] < sums[i] + u); ++j);
            if(j == sz || sums[j] != sums[i] + u)
                return 0;
            vis[j] = 1;
            ret.push_back(sums[i]);
            hasZero |= !sums[i];
        }
        if(!hasZero) {
            for(int &x: ret) {
                x += u;
                hasZero |= !x;
            }
            u = -u;
        }
        sums = move(ret);
        return hasZero;
    }
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        sort(sums.begin(), sums.end());
        // assert(sums.back() >= 0 && *lower_bound(sums.begin(), sums.end(), 0) == 0);
        if(sums.back() < 0 || *lower_bound(sums.begin(), sums.end(), 0) != 0)
            return {};
        vector<int> ret;
        while(sums.size() > 1) {
            int u = sums[1] - sums[0];
            // assert(reduce(sums, u));
            if(!reduce(sums, u))
                return {};
            ret.push_back(u);
        }
        return ret;
    }
};
