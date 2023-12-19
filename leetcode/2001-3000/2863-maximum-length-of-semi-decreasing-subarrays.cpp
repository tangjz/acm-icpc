class Solution {
public:
    int maxSubarrayLength(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> stk;
        for(int i = 0; i < n; ++i)
            if(stk.empty() || nums[stk.back()] < nums[i])
                stk.push_back(i);
        if(stk.empty())
            return ans;
        for(int i = n - 1; i >= 0; --i) {
            while(nums[i] < nums[stk.back()]) {
                ans = max(ans, i - stk.back() + 1);
                stk.pop_back();
                if(stk.empty())
                    return ans;
            }
            if(i > stk.back())
                continue;
            stk.pop_back();
            if(stk.empty())
                return ans;
        }
        return ans;
    }
};
