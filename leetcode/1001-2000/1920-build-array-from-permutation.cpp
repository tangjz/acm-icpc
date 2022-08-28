class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        vector<int> ret;
        for(int x: nums)
            ret.push_back(nums[x]);
        return ret;
    }
};
