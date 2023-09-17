class Solution {
public:
    int accountBalanceAfterPurchase(int x) {
        int y = x / 10 * 10, z = y + 10;
        return 100 - (x - y < z - x ? y : z);
    }
};
