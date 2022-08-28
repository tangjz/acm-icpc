class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i)
            for(int j = i + 1, k = j + 1; j < n; ++j) {
                for( ; k < n && nums[i] + nums[j] > nums[k]; ++k);
                ans += max(k - j - 1, 0);
            }
        return ans;
    }
};
