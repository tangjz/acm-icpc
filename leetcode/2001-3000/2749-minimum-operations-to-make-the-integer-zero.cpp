class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        typedef long long LL;
        LL res = num1;
        for(int i = 1; i <= 60 && (res -= num2) >= i; ++i) {
            if(__builtin_popcountll(res) <= i)
                return i;
        }
        return -1;
    }
};
