class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int pos = 0, lft = 0, rht = 0;
        for(int x : nums)
            pos ^= x;
        if(pos != INT_MIN)
            pos &= -pos;
        for(int x : nums)
            (x & pos ? lft : rht) ^= x;
        return {lft, rht};
    }
};
