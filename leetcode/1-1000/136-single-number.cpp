class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for(int x: nums)
            ret ^= x;
        return ret;
    }
};
