class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int L = 1, R = *max_element(nums.begin(), nums.end());
        while(L < R) {
            int M = (L + R) >> 1;
            long long sum = 0;
            for(int x : nums) {
                sum += (x - 1) / M + 1;
                if(sum > threshold)
                    break;
            }
            if(sum > threshold) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};
