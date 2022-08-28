class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN, pre = 0;
        for(int x: nums) {
            pre = max(pre, 0) + x;
            ans = max(ans, pre);
        }
        return ans;
    }
};
