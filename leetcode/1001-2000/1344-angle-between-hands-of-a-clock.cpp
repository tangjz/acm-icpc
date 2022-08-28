class Solution {
public:
    double angleClock(int hour, int minutes) {
        const int maxd = 12 * 60, delta = maxd / 360;
        int dis = abs(hour * 60 - minutes * 11);
        return min(dis, maxd - dis) / (double)delta;
    }
};
