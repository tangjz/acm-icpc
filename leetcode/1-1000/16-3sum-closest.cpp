class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size(), val = nums[0] + nums[1] + nums[2], ans = abs(val - target);
        sort(nums.begin(), nums.end());
        for(int i, j = 1, k; j + 1 < n; ++j)
            for(i = j - 1, k = j + 1; i >= 0 && k < n; ) {
                int cur = nums[i] + nums[j] + nums[k], dt = cur - target;
                if(!dt)
                    return target;
                if(dt < 0) {
                    ++k;
                } else {
                    --i;
                }
                dt = abs(dt);
                if(dt < ans) {
                    val = cur;
                    ans = dt;
                }
            }
        return val;
    }
};
