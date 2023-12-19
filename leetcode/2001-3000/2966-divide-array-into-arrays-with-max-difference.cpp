class Solution {
public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int> > ret;
        for(int i = 0; i < n; i += 3) {
            if(nums[i + 2] - nums[i] > k)
                return {};
            ret.push_back(vector<int>(nums.begin() + i, nums.begin() + i + 3));
        }
        return ret;
    }
};
