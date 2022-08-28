class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int n = nums.size(), sg = 0;
        for(int x: nums)
            sg ^= x;
        return !sg || !(n & 1);
    }
};
