class Solution {
public:
    int maximizeGreatness(vector<int>& nums) {
        int n = nums.size(), L = 0, R = n;
        sort(nums.begin(), nums.end());
        while(L < R) {
            int M = (L + R + 1) >> 1;
            bool bad = 0;
            for(int i = 0; i < M; ++i)
                if(nums[i] >= nums[n - M + i]) {
                    bad = 1;
                    break;
                }
            if(bad) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L;
    }
};
