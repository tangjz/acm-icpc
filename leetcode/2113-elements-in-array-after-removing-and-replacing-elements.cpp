class Solution {
public:
    vector<int> elementInNums(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> ret;
        for(auto &it: queries) {
            int t = it[0] % (n + n), p;
            if(t < n) {
                p = it[1] + t;
            } else {
                p = it[1] < t - n ? it[1] : n;
            }
            ret.push_back(p < n ? nums[p] : -1);
        }
        return ret;
    }
};
