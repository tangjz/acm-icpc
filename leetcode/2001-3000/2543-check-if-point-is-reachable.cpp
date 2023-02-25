class Solution {
public:
    bool isReachable(int x, int y) {
        int com = gcd(x, y);
        return !(com & (com - 1));
    }
};
