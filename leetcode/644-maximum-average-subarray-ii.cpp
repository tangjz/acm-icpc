class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double L = INT_MAX, R = INT_MIN;
        for(int x: nums)
            if(x < L) {
                L = x;
            } else if(x > R) {
                R = x;
            }
        int n = nums.size();
        while(R - L >= 1e-5) {
            double M = (L + R) / 2;
            double pre = INT_MAX, cur = 0, sum = 0;
            for(int i = 0; i < n; ++i) {
                double val = nums[i] - M;
                cur += val;
                sum += val;
                if(i >= k - 1) {
                    pre = min(pre, cur - sum);
                    if(cur >= pre)
                        break;
                    sum -= nums[i - k + 1] - M;
                }
            }
            if(cur >= pre) {
                L = M;
            } else {
                R = M;
            }
        }
        return L;
    }
};
