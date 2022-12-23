class Solution {
public:
    int distinctAverages(vector<int>& nums) {
        int n = nums.size() / 2;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i)
            nums[i] += nums[n + n - 1 - i];
        nums.resize(n);
        sort(nums.begin(), nums.end());
        return unique(nums.begin(), nums.end()) - nums.begin();
    }
};
