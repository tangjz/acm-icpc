class Solution {
    static int sgn(double x) {
        static const double eps = 1e-9;
        return (x > eps) - (x < -eps);
    }
    struct Point {
        double x, y;
        Point operator - (Point const &t) const {
            return (Point){x - t.x, y - t.y};
        }
        Point operator + (Point const &t) const {
            return (Point){x + t.x, y + t.y};
        }
        Point operator * (double const &t) const {
            return (Point){x * t, y * t};
        }
        double det(Point const &t) const {
            return x * t.y - y * t.x;
        }
        double dot(Point const &t) const {
            return x * t.x + y * t.y;
        }
        double len() const {
            return sqrtl(dot(*this));
        }
    };
    struct Circle {
        Point c;
        double r;
        bool inner(Point const &t) const {
            return sgn((t - c).len() - r) <= 0;
        }
    };
    Circle circumscribedCircle(vector<Point> const &vec) {
        static Point mat[3];
        static double len2[3];
        auto calc = [&]() {
            double ret = 0;
            for(int i = 0, j = 2; i < 3; j = i++)
                ret += mat[j].det(mat[i]);
            return ret;
        };
        for(int i = 0; i < 3; ++i) {
            len2[i] = vec[i].dot(vec[i]);
            mat[i] = vec[i];
        }
        double den = calc() * 2;
        for(int i = 0; i < 3; ++i)
            mat[i].x = len2[i];
        double x = calc() / den;
        for(int i = 0; i < 3; ++i)
            mat[i] = {vec[i].x, len2[i]};
        double y = calc() / den;
        Point c = {x, y};
        return {c, (vec[0] - c).len()};
    }
public:
    vector<double> outerTrees(vector<vector<int>>& trees) {
        static mt19937 rnd(time(nullptr));
        int n = trees.size();
        vector<Point> p(n);
        for(int i = 0; i < n; ++i) {
            p[i].x = trees[i][0];
            p[i].y = trees[i][1];
        }
        shuffle(p.begin(), p.end(), rnd);
        Circle ret = {p[0], 0};
        for(int i = 1; i < n; ++i) {
            if(ret.inner(p[i]))
                continue;
            ret = {p[i], 0};
            for(int j = 0; j < i; ++j) {
                if(ret.inner(p[j]))
                    continue;
                ret.c = (p[i] + p[j]) * 0.5;
                ret.r = (p[j] - ret.c).len();
                for(int k = 0; k < j; ++k) {
                    if(ret.inner(p[k]))
                        continue;
                    ret = circumscribedCircle({p[k], p[j], p[i]});
                }
            }
        }
        return {ret.c.x, ret.c.y, ret.r};
    }
};
