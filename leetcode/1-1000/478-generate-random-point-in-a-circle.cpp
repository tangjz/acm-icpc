class Solution {
    mt19937 rnd;
    double randCoordinate() {
        uniform_real_distribution<> dis(-1, nextafter(1, numeric_limits<double>::max()));
        return dis(rnd);
    }
    double rad, ox, oy;
public:
    Solution(double radius, double x_center, double y_center) : rad(radius), ox(x_center), oy(y_center), rnd(time(NULL)) {}

    vector<double> randPoint() {
        double dx, dy;
        do {
            dx = randCoordinate();
            dy = randCoordinate();
        } while(dx * dx + dy * dy > 1);
        return {ox + rad * dx, oy + rad * dy};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */
