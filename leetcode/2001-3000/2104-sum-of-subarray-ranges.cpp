class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        for(int i = 0; i < n; ++i) {
            int low = nums[i], upp = nums[i];
            for(int j = i; j < n; ++j) {
                if(nums[j] < low) {
                    low = nums[j];
                } else if(nums[j] > upp) {
                    upp = nums[j];
                }
                ans += upp - low;
            }
        }
        return ans;
    }
};
