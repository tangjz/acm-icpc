class Solution {
public:
    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {
        static const int mod = (int)1e9 + 7;
        int n = nums.size(), m = queries.size(), sq = ceil(sqrtl(n));
        vector<int> ret(m), suf(n);
        vector<vector<int> > idx(sq);
        for(int i = 0; i < m; ++i) {
            int j = queries[i][0], dt = queries[i][1];
            if(dt < sq) {
                idx[dt].push_back(i);
                continue;
            }
            for( ; j < n; j += dt)
                (ret[i] += nums[j]) >= mod && (ret[i] -= mod);
        }
        for(int dt = 1; dt < sq; ++dt) {
            if(idx[dt].empty())
                continue;
            for(int j = n - 1, k = j + dt; j >= 0; --j, --k) {
                suf[j] = nums[j];
                k < n && (suf[j] += suf[k]) >= mod && (suf[j] -= mod);
            }
            for(int i: idx[dt])
                ret[i] = suf[queries[i][0]];
        }
        return ret;
    }
};
