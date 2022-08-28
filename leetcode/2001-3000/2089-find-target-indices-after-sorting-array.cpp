class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int cL = 0, cE = 0;
        for(int x: nums) {
            cL += x < target;
            cE += x == target;
        }
        vector<int> ret(cE);
        iota(ret.begin(), ret.end(), cL);
        return ret;
    }
};
