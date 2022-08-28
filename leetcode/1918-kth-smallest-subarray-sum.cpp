class Solution {
public:
    int kthSmallestSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(), L = 0, R = (int)1e9;
        while(L < R) {
            int M = (L + R) / 2, ctr = 0;
            for(int i = 0, j = 0, s = 0; i < n; ++i) {
                s += nums[i];
                for( ; s > M; s -= nums[j++]);
                ctr += i - j + 1;
            }
            if(ctr < k) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};
