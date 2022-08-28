class Solution {
public:
    int arraySign(vector<int>& nums) {
        int sgn = 1;
        for(int x: nums)
            sgn *= max(min(x, 1), -1);
        return sgn;
    }
};
