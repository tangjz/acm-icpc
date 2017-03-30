#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 200001;
struct Point {
	LL x, y;
	void read() {
		scanf("%lld%lld", &x, &y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	LL dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	LL det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	LL norm2() const {
		return dot(*this);
	}
	bool operator < (const Point &t) const {
		if(!y && !t.y && (LL)x * t.x <= 0)
			return x > t.x;
		if(!y && x >= 0 && t.y != 0)
			return 1;
		if(!t.y && t.x >= 0 && y != 0)
			return 0;
		if((LL)t.y * y <= 0)
			return y > t.y;
		LL tmp = det(t);
		return tmp > 0; // || tmp == 0 && norm() < t.norm2();
	}
} a[maxn];
int n;
LL ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		a[i].read();
	std::sort(a, a + n);
	for(int i = 0; i < n; ++i)
		a[n + i] = a[i];
	Point vec = {};
	for(int i = 0, j = 0; i < n; vec = vec - a[i++], ans = std::max(ans, vec.norm2()))
		for( ; j < i + n && a[i].det(a[j]) >= 0; vec = vec + a[j++], ans = std::max(ans, vec.norm2()));
	printf("%lld.000\n", ans);
	return 0;
}
