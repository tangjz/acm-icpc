class Solution {
public:
    int minOperations(vector<int>& nums, int x, int y) {
        int n = nums.size();
        x -= y;
        int L = 0, R = (*max_element(nums.begin(), nums.end()) - 1) / y + 1;
        while(L < R) {
            int M = (L + R) >> 1;
            int rem = M;
            for(int u: nums) {
                u -= y * M;
                if(u <= 0)
                    continue;
                u = (u - 1) / x + 1;
                rem -= u;
                if(rem < 0)
                    break;
            }
            if(rem < 0) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};