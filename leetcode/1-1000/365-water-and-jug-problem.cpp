class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        return z <= x + y && z % gcd(x, y) == 0;
    }
};
