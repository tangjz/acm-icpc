typedef long long LL;
typedef double DB;
const int maxn = 1009;
const DB eps = 1e-6;
inline int sgn(DB x) {
	assert(!std::isnan(x));
	return (x > eps) - (x < -eps);
}
int n, tot;
struct Point {
	DB x, y;
	bool operator == (Point const &t) const {
		return !sgn(x - t.x) && !sgn(y - t.y);
	}
	bool operator < (Point const &t) const {
		return sgn(x - t.x) ? sgn(x - t.x) < 0 : sgn(y - t.y) < 0;
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator * (DB const &t) const {
		return (Point){x * t, y * t};
	}
	DB dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	DB norm() const {
		return sqrt(dot(*this));
	}
} p[maxn];
struct Line {
	Point a, b;
	void init(Point const &a, Point const &b) {
		this -> a = a;
		this -> b = b;
	}
	bool parallel(Line const &t) const {
		return !sgn((b - a).det(t.b - t.a));
	}
	bool on_line(Point const &t) const {
		return !sgn((b - a).det(t - a));
	}
	bool on_seg(Point const &t) const {
		Point u = t - a, v = t - b;
		return !sgn(u.det(v)) && sgn(u.dot(v)) <= 0;
	}
	bool on_left(Point const &t) const { // not strictly
		return sgn((b - a).det(t - a)) >= 0;
	}
	bool has_intersect(Line const &t) const { // Line.funct(Segment)
		return sgn((b - a).det(t.b - a)) * sgn((b - a).det(t.a - a)) <= 0;
	}
	Point intersect(Line const &t) const {
		Point u = a - t.a, v = b - a, w = t.b - t.a;
		return a + v * (w.det(u) / v.det(w));
	}
} line[maxn];
struct Node {
	int ref;
	Point p;
	bool operator < (Node const &t) const {
		return p < t.p;
	}
} ins[maxn << 1 | 1];

class Solution {
public:
    bool isPointInPolygon(double x, double y, vector<double>& coords) {
        n = coords.size() / 2 - 1;
        for(int i = 0; i < n; ++i) {
            p[i].x = coords[i + i];
            p[i].y = coords[i + i + 1];
        }
        p[n].x = x;
        p[n].y = y;
        for(int i = 0; i < n; ++i)
            if(p[i] == p[n])
                return 0;
        Line seg;
        if(n == 1)
            return p[0] == p[n];
        if(n == 2) {
            seg.init(p[0], p[1]);
            return seg.on_seg(p[n]);
        }
        rotate(p, min_element(p, p + n), p + n);
        if(sgn((p[0] - p[n - 1]).det(p[1] - p[0])) < 0)
            reverse(p + 1, p + n);
        Line sp;
        sp.a.x = sp.b.x = x;
        sp.a.y = -20000;
        sp.b.y = 20000;
        tot = 0;
        for(int i = 0, j = n - 1; i < n; j = i++) {
            line[i].init(p[j], p[i]);
            if(line[i].on_seg(p[n]))
                return 0;
            if(!sp.parallel(line[i])) {
                Point tmp = sp.intersect(line[i]);
                if(!line[i].on_seg(tmp))
                    continue;
                ins[tot++] = (Node){i, tmp};
            } else if(sp.on_line(line[i].a)) {
                ins[tot++] = (Node){i, line[i].a};
                ins[tot++] = (Node){i, line[i].b};
            }
        }
    	sort(ins, ins + tot);
        for(int i = 0, inner = 0; i < tot; ++i) {
            if(i > 0) {
                seg.init(ins[i - 1].p, ins[i].p);
                if(seg.on_seg(p[n]))
                    return inner;
            }
            if(i + 1 < tot && ins[i].p == ins[i + 1].p) {
                if(i + 3 < tot && ins[i + 2].p == ins[i + 3].p) {
                    int seq[4] = {ins[i].ref, ins[i + 1].ref, ins[i + 2].ref, ins[i + 3].ref};
                    sort(seq, seq + 4);
                    int refM = -1;
                    for(int j = 1; j < 4; ++j)
                        if(seq[j - 1] == seq[j]) {
                            assert(refM == -1);
                            refM = seq[j];
                        }
                    if(refM >= 0) { // cover an edge
                        int refL = ins[i].ref == refM ? ins[i + 1].ref : ins[i].ref;
                        int refR = ins[i + 2].ref == refM ? ins[i + 3].ref : ins[i + 2].ref;
                        Line tmp;
                        Point a = line[refL].a == ins[i].p ? line[refL].b : line[refL].a;
                        Point b = line[refR].a == ins[i + 2].p ? line[refR].b : line[refR].a;
                        tmp.init(a, b);
                        if(sp.has_intersect(tmp))
                            inner ^= 1;
                        i += 3;
                        continue;
                    }
                } // cross an vertex
                int refL = ins[i].ref, refR = ins[i + 1].ref;
                Line tmp;
                Point a = line[refL].a == ins[i].p ? line[refL].b : line[refL].a;
                Point b = line[refR].a == ins[i + 1].p ? line[refR].b : line[refR].a;
                tmp.init(a, b);
                if(sp.has_intersect(tmp))
                    inner ^= 1;
                ++i;
                continue;
            } // cross an edge
            inner ^= 1;
        }
        return 0;
    }
};
