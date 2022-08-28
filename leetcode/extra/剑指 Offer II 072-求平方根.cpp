class Solution {
public:
    int mySqrt(int x) {
        typedef long long LL;
        int y = min(max(x / 2, 1), x);
        while(!((LL)y * y <= x && (y + 1LL) * (y + 1LL) > x))
            y = (y + x / y) / 2;
        return y;
    }
};
