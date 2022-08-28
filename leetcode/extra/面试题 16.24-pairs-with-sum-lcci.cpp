class Solution {
public:
    vector<vector<int>> pairSums(vector<int>& nums, int target) {
        unordered_map<int, int> ctr;
        vector<vector<int> > ret;
        for(int x: nums) {
            long long y = (long long)target - x;
            if(y < INT_MIN || y > INT_MAX)
                continue;
            auto it = ctr.find((int)y);
            if(it == ctr.end()) {
                ++ctr[x];
                continue;
            }
            ret.push_back({x, (int)y});
            if(!(--(it -> second)))
                ctr.erase(it -> first);
        }
        return ret;
    }
};
