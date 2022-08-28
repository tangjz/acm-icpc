class Solution {
    int sgn(int x) {
        return (x > 0) - (x < 0);
    }
public:
    bool isMonotonic(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2)
            return 1;
        int dif = sgn(nums[1] - nums[0]);
        for(int i = 2; i < n; ++i) {
            int cur = sgn(nums[i] - nums[i - 1]);
            if(dif * cur < 0)
                return 0;
            if(!dif)
                dif = cur;
        }
        return 1;
    }
};
