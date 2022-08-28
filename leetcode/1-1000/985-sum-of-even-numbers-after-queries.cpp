class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int ans = 0;
        for(int x: nums)
            !(x & 1) && (ans += x);
        vector<int> ret;
        for(auto &it: queries) {
            int &x = nums[it[1]];
            !(x & 1) && (ans -= x);
            x += it[0];
            !(x & 1) && (ans += x);
            ret.push_back(ans);
        }
        return ret;
    }
};
