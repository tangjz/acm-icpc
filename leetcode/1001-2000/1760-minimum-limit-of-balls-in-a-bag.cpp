class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int L = 1, R = *max_element(nums.begin(), nums.end());
        while(L < R) {
            int M = (L + R) >> 1, cnt = 0;
            for(int x: nums) {
                int c = (x - 1) / M + 1;
                cnt += c - 1;
            }
            if(cnt <= maxOperations) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
