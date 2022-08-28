class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size(), ans = INT_MIN;
        for(int i = 0, s = 0; i < n; ++i) {
            if(i - k >= 0)
                s -= nums[i - k];
            s += nums[i];
            if(i >= k - 1)
                ans = max(ans, s);
        }
        return (double)ans / k;
    }
};
