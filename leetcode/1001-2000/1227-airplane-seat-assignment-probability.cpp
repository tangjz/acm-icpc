class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        return 1.0 / min(n, 2);
    }
};
