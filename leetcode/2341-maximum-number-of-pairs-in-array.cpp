class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        vector<int> ret = {0, 0};
        for(auto &it: ctr) {
            ret[0] += it.second >> 1;
            ret[1] += it.second & 1;
        }
        return ret;
    }
};
