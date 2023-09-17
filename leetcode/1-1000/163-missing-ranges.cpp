class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<vector<int> > ret;
        int las = lower;
        for(int x: nums) {
            if(las < x)
                ret.push_back({las, x - 1});
            las = x + 1;
        }
        if(las <= upper)
            ret.push_back({las, upper});
        return ret;
    }
};
