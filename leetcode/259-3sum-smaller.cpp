class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size(), ans = 0;
        sort(nums.begin(), nums.end());
        for(int i = 1; i + 1 < n; ++i)
            for(int j = i - 1, k = i + 1; j >= 0; --j) {
                for( ; k < n && nums[j] + nums[i] + nums[k] < target; ++k);
                ans += k - i - 1;
            }
        return ans;
    }
};
