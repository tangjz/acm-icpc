class Solution {
public:
    bool checkArray(vector<int>& nums, int k) {
        int n = nums.size();
        nums.push_back(0);
        for(int i = n; i > 0; --i)
            nums[i] -= nums[i - 1];
        for(int i = 0, r = 0; i <= n; ++i, (++r) == k && (r = 0)) {
            if(i > r)
                nums[r] += nums[i];
            if(nums[r] < 0)
                return 0;
        }
        return 1;
    }
};
