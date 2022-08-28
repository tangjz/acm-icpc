class Solution {
	typedef double DB;
	static constexpr DB eps = 1e-9;
	int sgn(DB x) {
		return (x > eps) - (x < -eps);
	}
	int dcmp(DB x, DB y) {
		return sgn(x - y);
	}
	struct Point {
		DB x, y;
		Point operator - (Point const &t) const {
			return (Point){x - t.x, y - t.y};
		}
		Point operator + (Point const &t) const {
			return (Point){x + t.x, y + t.y};
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
		DB len2() const {
			return dot(*this);
		}
		DB len() const {
			return sqrtl(max(dot(*this), (DB)0));
		}
	};
    Point LineLineIntersection(Point p1, Point p2, Point q1, Point q2) {
        return p1 + (p2 - p1) * ((q2 - q1).det(p1 - q1) / (p2 - p1).det(q2 - q1));
    }
    // bool debug;
    bool inter(vector<int> &A, vector<int> &B) {
        if(A.size() > B.size())
            return inter(B, A);
        if(A.size() == 4) {
            // seg-seg
            Point p1 = (Point){(DB)A[0], (DB)A[1]}, p2 = (Point){(DB)A[2], (DB)A[3]};
            Point q1 = (Point){(DB)B[0], (DB)B[1]}, q2 = (Point){(DB)B[2], (DB)B[3]};
            double num = (q2 - q1).det(p1 - q1), dom = (p2 - p1).det(q2 - q1);
            if(!sgn(dom))
                return 0;
            if(sgn(dom) < 0) {
                num = -num;
                dom = -dom;
            }
            Point com = p1 + (p2 - p1) * (num / dom), v2 = q2 - q1;
            double num2 = (com - q1).x, dom2 = v2.x;
            if(!sgn(dom2)) {
                num2 = (com - q1).y;
                dom2 = v2.y;
            }
            if(sgn(dom2) < 0) {
                num2 = -num2;
                dom2 = -dom2;
            }
            // if(debug) {
            //     printf("(%f, %f)-(%f, %f) (%f,%f)-(%f,%f): (%f, %f)\n", p1.x, p1.y, p2.x, p2.y, q1.x, q1.y, q2.x, q2.y, com.x, com.y);
            //     printf("%f, %f, %f, %f\n", num, dom, num2, dom2);
            // }
            return sgn(num) >= 0 && sgn(num - dom) <= 0 && sgn(num2) >= 0 && sgn(num2 - dom2) <= 0;
        }
        if(B.size() == 3) {
            // cir-cir
            Point cA = (Point){(DB)A[0], (DB)A[1]}, cB = (Point){(DB)B[0], (DB)B[1]};
            double rA = A[2], rB = B[2];
            Point vec = cB - cA;
            DB dis = vec.len();
            return sgn(rA + rB - dis) >= 0 && sgn(fabs(rA - rB) - dis) <= 0;
        }
        // cir-seg
        Point o = (Point){(DB)A[0], (DB)A[1]}, p1 = (Point){(DB)B[0], (DB)B[1]}, p2 = (Point){(DB)B[2], (DB)B[3]};
        double r = A[2];
        Point v = p2 - p1;
    	Point p = LineLineIntersection(o, (Point){o.x + v.y, o.y - v.x}, p1, p2);
        DB num = r * r - (p - o).len2(), den = v.len2();
        if(!sgn(den))
            return !sgn(num);
        if(sgn(num) < 0)
            return 0;
        DB q = sqrtl((p - p1).len2() / den), k = sqrtl(num / den);
        if(sgn((p - p1).dot(v)) < 0)
            q = -q;
        DB t1 = q - k, t2 = q + k;
        // if(debug) {
        //     printf("(%f, %f)-(%f, %f) (%f, %f)-%f: (%f, %f)\n", p1.x, p1.y, p2.x, p2.y, o.x, o.y, r, p.x, p.y);
        //     printf("%f, %f, %f, %f\n", q, k, t1, t2);
        // }
        return (sgn(t1) >= 0 && sgn(t1 - 1) <= 0) || (sgn(t2) >= 0 && sgn(t2 - 1) <= 0);
    }
public:
    vector<bool> antPass(vector<vector<int>>& seq, vector<vector<int>>& que) {
        int n = seq.size();
        vector<int> dsu(n, -1);
        function<int(int)> dsuFind = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsuFind(dsu[u]));
        };
        auto dsuMerge = [&](int u, int v) {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        for(int i = 0; i < n; ++i) {
            // if(i == 36 || i == 4 || i == 35) {
            //     printf("point %d: ", i);
            //     for(int x: seq[i])
            //         printf("%d ", x);
            //     puts("");
            //     debug = 1;
            // } else {
            //     debug = 0;
            // }
            for(int j = i + 1; j < n; ++j)
                if(inter(seq[i], seq[j])) {
                    // printf("inter %d %d\n", i, j);
                    dsuMerge(i, j);
                }
        }
        vector<bool> ret;
        for(auto &it: que)
            ret.push_back(dsuFind(it[0]) == dsuFind(it[1]));
        return ret;
    }
};
