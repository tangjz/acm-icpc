class Solution {
public:
    int findMaxCI(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for(int i = 0, j; i < n; ) {
            for(j = i++; i < n && nums[i] > nums[i - 1]; ++i);
            ans = max(ans, i - j);
        }
        return ans;
    }
};
