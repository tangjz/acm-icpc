class Solution {
public:
    bool findSubarrays(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> vis;
        for(int i = 1; i < n; ++i)
            if(!vis.insert(nums[i] + nums[i - 1]).second)
                return 1;
        return 0;
    }
};
