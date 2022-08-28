class Solution {
    string gen(int L, int R) {
        if(L == R)
            return to_string(L);
        return to_string(L) + "->" + to_string(R);
    }
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ret;
        int las = lower;
        for(int x: nums) {
            if(las < x)
                ret.push_back(move(gen(las, x - 1)));
            las = x + 1;
        }
        if(las <= upper)
            ret.push_back(move(gen(las, upper)));
        return ret;
    }
};
