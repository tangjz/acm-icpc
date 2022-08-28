class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int n = (int)nums.size();
        vector<int> ctr(n + 1);
        for(auto &it : requests) {
            ++ctr[it[0]];
            --ctr[it[1] + 1];
        }
        for(int i = 1; i < n; ++i)
            ctr[i] += ctr[i - 1];
        ctr.pop_back();
        sort(ctr.begin(), ctr.end());
        sort(nums.begin(), nums.end());

        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans = (ans + (LL)nums[i] * ctr[i]) % mod;
        return ans;
    }
};
