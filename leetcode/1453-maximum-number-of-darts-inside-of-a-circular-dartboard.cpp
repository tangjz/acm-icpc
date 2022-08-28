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
		DB len() const {
			return sqrtl(max(dot(*this), (DB)0));
		}
	};
	vector<Point> getCircleCircleIntersection(Point A, Point B, int r) {
		vector<Point> ret;
		Point vec = B - A;
		DB dis = vec.len();
		if(sgn(dis) == 0) {
			ret.push_back(A);
			return ret;
		}
		if(sgn(r + r - dis) < 0)
			return ret;
		DB dt = sqrtl(r * r - dis * dis / 4);
		Point M = (A + B) * ((DB)1 / 2);
		tie(vec.x, vec.y) = make_pair(-vec.y, vec.x);
		ret.push_back(M + (vec * (dt / dis)));
		ret.push_back(M - (vec * (dt / dis)));
		//printf("(%f, %f) (%f, %f) : (%f, %f) (%f, %f)\n", A.x, A.y, B.x, B.y, ret[0].x, ret[0].y, ret[1].x, ret[1].y);
		return ret;
	}
public:
	int numPoints(vector<vector<int>>& points, int r) {
		int n = (int)points.size();
		vector<Point> p, q;
		for(int i = 0; i < n; ++i) {
			p.push_back((Point){(DB)points[i][0], (DB)points[i][1]});
			for(int j = 0; j < i; ++j) {
				vector<Point> ins = getCircleCircleIntersection(p[i], p[j], r);
				for(auto &it : ins)
					q.push_back(it);
			}
			q.push_back(p[i]);
		}
		int ans = 1, m = (int)q.size();
		for(int i = 0; i < m; ++i) {
			int tmp = 0;
			for(int j = 0; j < n; ++j)
				tmp += sgn((p[j] - q[i]).len() - r) <= 0;
			ans = max(ans, tmp);
		}
		return ans;
	}
};
