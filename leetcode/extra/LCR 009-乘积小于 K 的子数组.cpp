class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = (int)nums.size(), prd = 1, ans = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && prd * nums[j] < k; prd *= nums[j++]);
            ans += j - i;
            if(j == i) {
                ++j;
            } else {
                prd /= nums[i];
            }
        }
        return ans;
    }
};
