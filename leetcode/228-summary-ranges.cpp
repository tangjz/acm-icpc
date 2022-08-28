class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int n = nums.size();
        vector<string> ret;
        for(int i = 0, j; i < n; i = j) {
            for(j = i + 1; j < n && nums[j - 1] == nums[j] - 1; ++j);
            if(j - i > 1) {
                ret.push_back(to_string(nums[i]) + "->" + to_string(nums[j - 1]));
            } else {
                ret.push_back(to_string(nums[i]));
            }
        }
        return ret;
    }
};
