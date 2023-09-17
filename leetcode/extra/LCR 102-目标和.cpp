class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size(), m = 1 << n, ans = 0;
        vector<pair<int, int> > seq(m);
        for(int i = 1; i < m; ++i) {
            int j = seq[i].first = i & 1 ? 0 : seq[i >> 1].first + 1;
            seq[i].second = seq[i ^ (1 << j)].second + nums[j];
            j = m - 1 - i;
            if(i > j) {
                int k = seq[i].second - seq[j].second;
                ans += (k == target) + (-k == target);
            }
        }
        return ans;
    }
};
