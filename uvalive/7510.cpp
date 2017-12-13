#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long double DB;
const int maxn = 51, maxt = 2501;
const DB eps = 1e-9;
inline DB rand_uniform() { // [-0.5, 0.5]
	return rand() / (DB)RAND_MAX - 0.5;
}
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
struct Point2D {
	DB x, y;
	bool operator < (Point2D const &t) const {
		int tmp = sgn(x - t.x);
		return tmp < 0 || (!tmp && sgn(y - t.y) < 0);
	}
	Point2D operator - (Point2D const &t) const {
		return (Point2D){x - t.x, y - t.y};
	}
	DB det(Point2D const &t) const {
		return x * t.y - y * t.x;
	}
} ori, p[maxn];
bool cmp(Point2D const &a, Point2D const &b) {
	return sgn((a - ori).det(b - ori)) > 0;
}
struct Point3D {
	DB x, y, z;
	void read() {
		double _x, _y, _z;
		scanf("%lf%lf%lf", &_x, &_y, &_z);
		x = _x, y = _y, z = _z;
	}
	Point3D operator - (Point3D const &t) const {
		return (Point3D){x - t.x, y - t.y, z - t.z};
	}
	Point3D operator + (Point3D const &t) const {
		return (Point3D){x + t.x, y + t.y, z + t.z};
	}
	Point3D operator * (DB const &t) const {
		return (Point3D){x * t, y * t, z * t};
	}
	DB dot(Point3D const &t) const {
		return x * t.x + y * t.y + z * t.z;
	}
	Point3D det(Point3D const &t) const {
		return (Point3D){y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x};
	}
	DB abs() const {
		return sqrt(dot(*this));
	}
	Point3D norm() const {
		return *this * (1 / abs());
	}
} a[maxn], f[maxn << 1 | 1];
int t, n, m, tot, ord[maxn];
bool vis[maxn][maxn][maxn];
int main() {
	srand(time(0));
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			a[i].read();
		m = 0;
		memset(vis, 0, sizeof vis);
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
				for(int k = j + 1; k < n; ++k) {
					if(vis[i][j][k])
						continue;
					Point3D vec = (a[j] - a[i]).det(a[k] - a[i]).norm();
					int sign = 0;
					tot = 0;
					for(int o = 0; o < n; ++o) {
						int tmp = sgn(vec.dot(a[o] - a[i]));
						if(!tmp)
							ord[tot++] = o;
						else if(!sign)
							sign = tmp;
						else if(sign != tmp) {
							sign = 0;
							break;
						}
					}
					if(!sign)
						continue;
					for(int ii = 0; ii < tot; ++ii)
						for(int jj = ii + 1; jj < tot; ++jj)
							for(int kk = jj + 1; kk < tot; ++kk)
								vis[ord[ii]][ord[jj]][ord[kk]] = 1;
					Point3D v1 = (a[j] - a[i]).norm(), v2 = vec.det(v1);
					for(int o = 0; o < tot; ++o) {
						p[o] = (Point2D){v1.dot(a[ord[o]]), v2.dot(a[ord[o]])};
						if(p[o] < p[0])
							std::swap(p[o], p[0]);
					}
					ori = p[tot] = p[0];
					std::sort(p + 1, p + tot, cmp);
					DB area = 0;
					for(int o = 0; o < tot; ++o)
						area += p[o].det(p[o + 1]);
					area *= -0.5 * sign;
					f[m++] = vec * area;
				}
		DB ans = 0;
		for(int tim = 0; tim < maxt; ++tim) {
			Point3D vec = (Point3D){rand_uniform(), rand_uniform(), rand_uniform()}, res = {};
			for(int i = 0; i < m; ++i)
				if(vec.dot(f[i]) > 0)
					res = res + f[i];
			ans = std::max(ans, res.abs());
		}
		printf("Case #%d: %.10f\n", Case, (double)ans);
	}
	return 0;
}
