class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ret;
        ret.reserve(k);
        set<pair<int, int> > sp;
        for(int i = 0, j = 0, las = -1; i < k; ++i) {
            for( ; j + k - i <= n; ++j)
                sp.insert({nums[j], j});
            int cur = sp.begin() -> second;
            ret.push_back(nums[cur]);
            while(las < cur) {
                ++las;
                sp.erase({nums[las], las});
            }
        }
        return ret;
    }
};
