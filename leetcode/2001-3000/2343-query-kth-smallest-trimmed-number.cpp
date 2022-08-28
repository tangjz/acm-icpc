class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        const int maxd = 10;
        int n = nums.size(), m = nums[0].size(), q = queries.size();
        vector<int> ord(n), ctr(maxd), ret(q, -1);
        vector<vector<int> > pos(m);
        iota(ord.begin(), ord.end(), 0);
        for(int i = 0; i < q; ++i)
            pos[queries[i][1] - 1].push_back(i);
        for(int i = 0; i < m; ++i) {
            vector<int> nxt(n, -1);
            ctr.assign(maxd, 0);
            for(int j = 0; j < n; ++j) {
                int o = nums[j][m - 1 - i] - '0';
                ++ctr[o];
            }
            for(int j = 1; j < maxd; ++j)
                ctr[j] += ctr[j - 1];
            for(int j = n - 1; j >= 0; --j) {
                int k = ord[j];
                int o = nums[k][m - 1 - i] - '0';
                nxt[--ctr[o]] = k;
            }
            ord = move(nxt);
            for(int j: pos[i])
                ret[j] = ord[queries[j][0] - 1];
        }
        return ret;
    }
};
