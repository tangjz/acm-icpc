class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), ans = n + 1;
        for(int i = 0, j = 0, s = 0; i < n; s -= nums[i++]) {
            for( ; j < n && s < target; s += nums[j++]);
            if(s >= target)
                ans = min(ans, j - i);
        }
        return ans <= n ? ans : 0;
    }
};
