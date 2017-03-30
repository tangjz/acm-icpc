#include <vector>
#include <stdio.h>
#include <cassert>
#include <algorithm>
using namespace std;
const int maxn = 51, maxm = 1001;
inline int sgn(int x) {
	return (x > 0) - (x < 0);
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
	int det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	bool operator < (const Point &t) const {
		if(!y && !t.y && x * t.x <= 0)
			return x > t.x;
		if(!y && x >= 0 && t.y != 0)
			return 1;
		if(!t.y && t.x >= 0 && y != 0)
			return 0;
		if(t.y * y <= 0)
			return y > t.y;
		int tmp = det(t);
		return tmp > 0;// || tmp == 0 && mode2() < t.mode2();
	}
	bool operator == (const Point &t) const {
		return x == t.x && y == t.y;
	}
	Point negate() const {
		return (Point){-x, -y};
	}
	Point characterize() const {
		assert(x || y);
		int r = __gcd(abs(x), abs(y));
		return (Point){x / r, y / r};
	}
};
struct Line {
	Point p, v;
	bool parallel(Line const &t) const {
		return !v.det(t.v);
	}
	bool intersect(Line const &t) const {
		int sgn1 = sgn(v.det(t.p - p)), sgn2 = sgn(v.det(t.p + t.v - p));
		int sgn3 = sgn(t.v.det(p - t.p)), sgn4 = sgn(t.v.det(p + v - t.p));
		return sgn1 * sgn2 + sgn3 * sgn4 < 0;
	}
	void reverse() {
		p = p + v;
		v = v.negate();
	}
};
struct Event {
	Point vec;
	int typ;
	Event() {}
	Event(Point _v, int _t) {
		vec = _v.characterize();
		typ = _t;
	}
	bool operator < (Event const &t) const {
		return vec < t.vec;
	}
};
int t, n, tot, cnt;
Line a[maxn];
Event que[maxm];
bool solve() // covered
{
	Point Min = que[0].vec, Max = que[0].vec;
	for(int i = 1; i < tot; ++i)
	{
		Point vec = que[i].vec;
		if(vec < Min)
			Min = vec;
		else if(Max < vec)
			Max = vec;
	}
	if(Min.det(Max) >= 0) // uncover
		return 0;
	Point dir = Min + Max;
	cnt = 0;
	for(int i = 0; i < tot; i += 2)
		if(dir.det(que[i].vec) <= 0 && dir.det(que[i + 1].vec) >= 0)
			++cnt;
	if(cnt == 0)
		return 0;
	sort(que, que + tot);
	for(int i = 0, j; i < tot; i = j)
	{
		for(j = i; j < tot && que[i].vec == que[j].vec; ++j)
			cnt += que[j].typ;
		if(cnt == 0)
			return 0;
	}
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			Point p, q;
			p.read();
			q.read();
			assert(!(p == q));
			a[i] = (Line){p, q - p};
		}
		bool chk = 0;
		tot = 0;
		for(int i = 0; i < n && !chk; ++i)
			for(int j = i + 1; j < n; ++j)
			{
				if(a[i].parallel(a[j]))
					continue;
				if(a[i].intersect(a[j]))
				{
					chk = 1;
					break;
				}
				Line A = a[i], B = a[j];
				if(A.p == B.p + B.v)
					B.reverse();
				if(A.p + A.v == B.p)
					A.reverse();
				if(A.p + A.v == B.p + B.v)
				{
					A.reverse();
					B.reverse();
				}
				if(A.p == B.p)
				{
					Point vA = A.v, vB = B.v;
					if(vA.det(vB) < 0)
						swap(vA, vB);
					que[tot++] = (Event){vB.negate(), 1};
					que[tot++] = (Event){vA, -1};
					que[tot++] = (Event){vB, 1};
					que[tot++] = (Event){vA.negate(), -1};
				}
			}
		puts(chk || solve() ? "Finite" : "Infinite");
	}
	return 0;
}
