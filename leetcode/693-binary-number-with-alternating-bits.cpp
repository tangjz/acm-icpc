class Solution {
public:
    bool hasAlternatingBits(int n) {
        return (n ^ (n >> 1)) == (1UL << (32 - __builtin_clz(n))) - 1;
    }
};
