class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        typedef pair<int, int> Point;
        auto rot = [&](Point s) -> Point {
            return {s.first + s.second, s.first - s.second};
        };
        auto flip = [&](Point s) -> Point {
            return {s.second, s.first};
        };
        auto calc = [&](Point s, Point p, Point t) -> int {
            if(s.first != t.first) {
                s = flip(s);
                p = flip(p);
                t = flip(t);
            }
            if(s.first != t.first)
                return 2;
            if(s.first != p.first)
                return 1;
            return (s.second - p.second) * (t.second - p.second) < 0 ? 2 : 1;
        };
        Point rk(a, b), bs(c, d), qn(e, f);
        return min(calc(rk, bs, qn), calc(rot(bs), rot(rk), rot(qn)));
    }
};
