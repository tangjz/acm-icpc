class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size(), ans = 0, sum = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            if(j < i) {
                j = i;
                sum = 0;
            }
            for( ; j < n && !(sum & nums[j]); sum |= nums[j++]);
            ans = max(ans, j - i);
            // printf("%d: %d %d\n", i, j, sum);
            sum ^= nums[i];
        }
        return ans;
    }
};
