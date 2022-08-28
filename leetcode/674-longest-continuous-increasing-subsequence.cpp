class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for(int i = 0, j; i < n; i = j) {
            for(j = i + 1; j < n && nums[j - 1] < nums[j]; ++j);
            ans = max(ans, j - i);
        }
        return ans;
    }
};
