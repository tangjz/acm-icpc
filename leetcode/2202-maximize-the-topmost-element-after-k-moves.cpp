class Solution {
public:
    int maximumTop(vector<int>& nums, int k) {
        int n = nums.size(), ans = -1;
        if(n == 1 && (k & 1))
            return ans;
        if(n > k)
            ans = max(ans, nums[k]);
        for(int i = 0; i < n && i < k - 1; ++i)
            ans = max(ans, nums[i]);
        return ans;
    }
};
