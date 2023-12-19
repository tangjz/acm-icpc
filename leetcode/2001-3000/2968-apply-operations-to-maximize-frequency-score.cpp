class Solution {
public:
    int maxFrequencyScore(vector<int>& nums, long long k) {
        typedef long long LL;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int L = 1, R = n;
        while(L < R) {
            int M = (L + R + 1) / 2;
            LL sum = 0, lft = 0;
            for(int i = 0; i < M; ++i) {
                sum += nums[i];
                if(i + i < M)
                    lft += nums[i];
            }
            LL res = sum - lft * 2 + (M & 1) * nums[(M - 1) / 2];
            for(int i = M; i < n; ++i) {
                sum += nums[i] - nums[i - M];
                lft += nums[i - M + 1 + (M - 1) / 2] - nums[i - M];
                res = min(res, sum - lft * 2 + (M & 1) * nums[i - M + 1 + (M - 1) / 2]);
            }
            if(res > k) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L;
    }
};
