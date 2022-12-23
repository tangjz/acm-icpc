class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int c1 = __builtin_popcount(num1), c2 = __builtin_popcount(num2);
        int ans = 0;
        for(int i = 0; c1 < c2; ++i)
            if(!((num1 >> i) & 1)) {
                ans ^= 1 << i;
                ++c1;
            }
        for(int i = 0; c1 > c2; ++i)
            if(((num1 >> i) & 1)) {
                ans ^= 1 << i;
                ++c2;
            }
        return ans ^ num1;
    }
};
