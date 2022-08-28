class Solution {
    vector<vector<int> > calc(vector<int>::iterator start, vector<int>::iterator end) {
        int n = end - start;
        vector<vector<int> > ret(n << 1 | 1);
        for(int i = 0; i < (1 << n); ++i) {
            int cnt = 0, sum = 0;
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1) {
                    ++cnt;
                    sum += *(start + j);
                } else {
                    --cnt;
                    sum -= *(start + j);
                }
            ret[n + cnt].push_back(sum);
        }
        for(int i = 0; i <= n + n; ++i) {
            sort(ret[i].begin(), ret[i].end());
            ret[i].erase(unique(ret[i].begin(), ret[i].end()), ret[i].end());
        }
        return move(ret);
    }
    int solve(vector<int> &lft, vector<int> &rht) {
        int n = lft.size(), m = rht.size();
        int ret = INT_MAX;
        for(int i = 0, j = m - 1; i < n; ++i) {
            for( ; j >= 0 && lft[i] + rht[j] > 0; --j);
            if(j >= 0)
                ret = min(ret, abs(lft[i] + rht[j]));
            if(j + 1 < m)
                ret = min(ret, abs(lft[i] + rht[j + 1]));
        }
        return ret;
    }
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size() >> 1;
        vector<vector<int> > lft = calc(nums.begin(), nums.begin() + n), rht = calc(nums.end() - n, nums.end());
        int ans = INT_MAX;
        for(int i = 0, j = n + n; j >= 0; ++i, --j) {
            ans = min(ans, solve(lft[i], rht[j]));
        }
        return ans;
    }
};
