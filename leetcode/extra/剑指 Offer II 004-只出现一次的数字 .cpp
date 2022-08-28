class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0, c;
        for(int x : nums) {
            c = (a ^ b) & x;
            a ^= ~b & x;
            b ^= c;
        }
        return a;
    }
};
