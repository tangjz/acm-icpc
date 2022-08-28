class Solution {
    bool check(vector<int> &nums, int c, int v) {
        int sum = 0;
        for(int x: nums) {
            if(sum + x > v) {
                sum = 0;
                --c;
            }
            if((sum += x) > v) {
                return 0;
            }
        }
        if(sum > 0)
            --c;
        return c >= 0;
    }
public:
    int splitArray(vector<int>& nums, int m) {
        int L = 0, R = (int)1e9;
        while(L < R) {
            int M = (L + R) >> 1;
            if(check(nums, m, M)) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
