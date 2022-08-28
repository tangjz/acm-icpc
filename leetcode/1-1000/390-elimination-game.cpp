class Solution {
    int calc(int n, bool fromLeft) {
        int m = (n + 1) >> 1;
        if(n == m)
            return fromLeft ? n - 1 : 0;
        return calc(n - m, !fromLeft) << 1 | (fromLeft || (n & 1));
    }
public:
    int lastRemaining(int n) {
        return calc(n, true) + 1;
    }
};
