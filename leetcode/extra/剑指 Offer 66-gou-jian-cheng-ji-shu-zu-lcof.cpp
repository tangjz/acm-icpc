class Solution {
public:
    vector<int> constructArr(vector<int>& nums) {
        vector<int> ret;
        ret.reserve(nums.size());
        int prd = 1;
        for(int x : nums) {
            ret.push_back(prd);
            prd *= x;
        }
        auto it = ret.rbegin(), jt = nums.rbegin();
        for(prd = 1; it != ret.rend(); ++it, ++jt) {
            *it *= prd;
            prd *= *jt;
        }
        return ret;
    }
};
