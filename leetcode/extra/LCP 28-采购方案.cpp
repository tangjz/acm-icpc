class Solution {
public:
    int purchasePlans(vector<int>& nums, int target) {
        typedef long long LL;
        int n = nums.size();
        LL ans = 0;
        sort(nums.begin(), nums.end());
        for(int i = 0, j = n - 1; i < n; ++i) {
            for(j = max(j, i); i < j && nums[i] + nums[j] > target; --j);
            ans += j - i;
        }
        return ans % ((int)1e9 + 7);
    }
};
