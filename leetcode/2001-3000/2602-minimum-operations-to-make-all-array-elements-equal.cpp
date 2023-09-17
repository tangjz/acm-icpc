class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
        typedef long long LL;
        int n = nums.size(), q = queries.size();
        vector<int> ord(q);
        vector<LL> ans(q);
        sort(nums.begin(), nums.end());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return queries[u] < queries[v];
        });
        LL sum = 0, low = 0;
        for(int x: nums)
            sum += x;
        for(int i = 0, j = 0; i < q; ++i) {
            int v = queries[ord[i]];
            for( ; j < n && v > nums[j]; low += nums[j++]);
            ans[ord[i]] = (LL)(j + j - n) * v + (sum - low - low);
        }
        return ans;
    }
};
