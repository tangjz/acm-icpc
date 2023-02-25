class Solution {
public:
    int minImpossibleOR(vector<int>& nums) {
        int ret = 1;
        sort(nums.begin(), nums.end());
        for(int x: nums)
            if(ret == x)
                ret <<= 1;
        return ret;
    }
};
