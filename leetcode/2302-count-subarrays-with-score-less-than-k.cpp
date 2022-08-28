class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        long long ans = 0, sum = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && max(j - i, 0) * sum < k; sum += nums[j++]);
            ans += j - i - (max(j - i, 0) * sum >= k);
            sum -= nums[i];
        }
        return ans;
    }
};
