class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), L = 0, R = n / 2;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            bool bad = 0;
            for(int i = 0; i < M; ++i)
                if(nums[i] * 2 > nums[n - M + i]) {
                    bad = 1;
                    break;
                }
            if(bad) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L * 2;
    }
};
