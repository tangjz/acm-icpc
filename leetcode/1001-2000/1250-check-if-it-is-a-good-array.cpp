class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        int com = 0;
        for(int x : nums)
            com = __gcd(com, x);
        return com == 1;
    }
};
