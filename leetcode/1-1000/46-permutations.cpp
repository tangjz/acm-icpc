class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > ret;
        sort(nums.begin(), nums.end());
        do {
            ret.push_back(nums);
        } while(next_permutation(nums.begin(), nums.end()));
        return ret;
    }
};
