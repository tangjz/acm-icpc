class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            ret.push_back(nums[i]);
            ret.push_back(nums[n + i]);
        }
        return ret;
    }
};
