class Solution {
public:
    int distanceTraveled(int a, int b) {
        a += min((a - 1) / 4, b);
        return a * 10;
    }
};
