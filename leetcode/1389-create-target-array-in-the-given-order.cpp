class Solution {
public:
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
        int n = (int)nums.size();
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            ret.push_back(nums[i]);
            rotate(ret.begin() + index[i], ret.end() - 1, ret.end());
        }
        return ret;
    }
};
