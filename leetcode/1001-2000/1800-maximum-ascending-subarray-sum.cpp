class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int ans = 0, n = (int)nums.size();
        for(int i = 0; i < n; ) {
            int sum = nums[i];
            for(++i; i < n && nums[i - 1] < nums[i]; ++i)
                sum += nums[i];
            ans = max(ans, sum);
        }
        return ans;
    }
};
