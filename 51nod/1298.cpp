#include <stdio.h>
typedef long long LL;
template<class T> inline int sgn(T const &x)
{
	return (x > 0) - (x < 0);
}
template<class T> inline T sqr(T x)
{
	return x * x;
}
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	int dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	int det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	int mode2() const {
		return dot(*this);
	}
} p[5];
int r;
inline bool check(int i, int j)
{
	int sgn1 = sgn((p[i] - p[0]).mode2() - sqr(r));
	int sgn2 = sgn((p[j] - p[0]).mode2() - sqr(r));
	if(sgn1 * sgn2 <= 0)
		return 1;
	if(sgn1 < 0 || sgn(sqr((LL)(p[0] - p[i]).det(p[j] - p[i])) - (LL)sqr(r) * (p[j] - p[i]).mode2()) > 0)
		return 0;
	return sgn((p[0] - p[i]).dot(p[j] - p[i])) >= 0 && sgn((p[0] - p[j]).dot(p[i] - p[j])) >= 0;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		p[0].read();
		scanf("%d", &r);
		for(int i = 1; i <= 3; ++i)
			p[i].read();
		puts(check(1, 2) || check(1, 3) || check(2, 3) ? "Yes" : "No");
	}
	return 0;
}
