class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int n = nums.size(), pos = -1;
        for(int i = 1; i < n; ++i)
            if(nums[i - 1] > nums[i])
                pos = pos == -1 ? i : -2;
        if(pos == -2)
            return 0;
        return pos == -1 || pos == 1 || pos == n - 1 || nums[pos - 2] <= nums[pos] || nums[pos - 1] <= nums[pos + 1];
    }
};
