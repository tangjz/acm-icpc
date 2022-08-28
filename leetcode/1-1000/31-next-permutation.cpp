class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = (int)nums.size();
        if(n <= 1)
            return;
        int i;
        for(i = n - 2; i >= 0 && nums[i] >= nums[i + 1]; --i);
        if(i < 0) {
            reverse(nums.begin(), nums.end());
            return;
        }
        int j;
        for(j = i + 1; j + 1 < n && nums[i] < nums[j + 1]; ++j);
        swap(nums[i], nums[j]);
        reverse(nums.begin() + i + 1, nums.end());
    }
};
