class Solution {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {
        int n = nums.size();
        unordered_map<int, int> Hash;
        for(int i = 0; i < n; ++i)
            Hash[nums[i]] = i;
        for(auto &it: operations) {
            int pos = Hash[it[0]];
            Hash.erase(it[0]);
            Hash[it[1]] = pos;
        }
        for(auto &it: Hash)
            nums[it.second] = it.first;
        return nums;
    }
};
