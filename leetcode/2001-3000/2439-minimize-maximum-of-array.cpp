class Solution {
public:
    int minimizeArrayValue(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size(), ans = 0;
        LL sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += nums[i];
            int upp = (sum + i) / (i + 1);
            ans = max(ans, upp);
        }
        return ans;
    }
};
