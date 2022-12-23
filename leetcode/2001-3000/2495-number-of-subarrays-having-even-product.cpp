class Solution {
public:
    long long evenProduct(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        LL ans = n * (n + 1LL) / 2;
        for(int i = 0, j; i < n; ) {
            for(j = i; i < n && !((nums[i] - nums[j]) & 1); ++i);
            if(nums[j] & 1) {
                j = i - j;
                ans -= j * (j + 1LL) / 2;
            }
        }
        return ans;
    }
};
