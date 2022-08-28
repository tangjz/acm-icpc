class Solution {
public:
    int findComplement(int num) {
        return num ^ ((1UL << (32 - __builtin_clz(num))) - 1);
    }
};
