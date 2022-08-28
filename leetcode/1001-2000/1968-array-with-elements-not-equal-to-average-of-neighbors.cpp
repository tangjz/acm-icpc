class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size(), m = (n + 1) >> 1;
        nth_element(nums.begin(), nums.begin() + m, nums.end());
        vector<int> ret;
        for(int i = 0; i < n; ++i)
            ret.push_back(nums[i & 1 ? (m + (i >> 1)) : (i >> 1)]);
        return ret;
    }
};
