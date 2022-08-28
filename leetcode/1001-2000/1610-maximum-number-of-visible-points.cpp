const double pi = acos(-1.0), eps = 1e-9;
class Solution {
    struct Point {
        int x, y;
        bool site() const {
            return x < 0 || (!x && y < 0);
        }
        int det(Point const &t) const {
            return x * t.y - y * t.x;
        }
        int dot(Point const &t) const {
            return x * t.x + y * t.y;
        }
        bool operator < (Point const &t) const {
            bool u = site(), v = t.site();
            return u < v || (u == v && det(t) > 0);
        }
    };
    int sgn(double x) {
        return (x > eps) - (x < -eps);
    }
    bool check(Point const &A, Point const &B, int dt) {
        int det = A.det(B), dot = A.dot(B);
        if(!det) {
            return dot > 0 || dt >= 180;
        }
        int lenA = A.dot(A), lenB = B.dot(B);
        // printf("(%d %d) (%d %d): %d %d %d %d: %.2Lf\n", A.x, A.y, B.x, B.y, det, dot, lenA, lenB, cos(dt / 180.0 * pi) * sqrtl(lenA * lenB));
        if(det > 0) {
            if(dt >= 180)
                return true;
            return sgn(dot - cos(dt / 180.0 * pi) * sqrtl(lenA * lenB)) >= 0;
        }
        if(dt <= 180)
            return false;
        return sgn(dot - cos(dt / 180.0 * pi) * sqrtl(lenA * lenB)) <= 0;
    }
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        int ans = 0, adt = 0;
        vector<Point> p;
        for(auto &it: points) {
            int x = it[0] - location[0];
            int y = it[1] - location[1];
            if(!x && !y) {
                ++adt;
                continue;
            }
            p.push_back((Point){x, y});
        }
        sort(p.begin(), p.end());
        int n = p.size();
        for(int i = 0; i < n; ++i)
            p.push_back(p[i]);
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n + i && check(p[i], p[j], angle); ++j);
            ans = max(ans, j - i);
        }
        return ans + adt;
    }
};
