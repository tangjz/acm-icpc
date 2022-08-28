class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = (int)nums.size(), ans = 0;
        unordered_set<int> vis;
        for(int i = 0, j = 0, tmp = 0; i < n; ++i) {
            for( ; j < n && !vis.count(nums[j]); ++j) {
                tmp += nums[j];
                vis.insert(nums[j]);
            }
            ans = max(ans, tmp);
            vis.erase(nums[i]);
            tmp -= nums[i];
        }
        return ans;
    }
};
