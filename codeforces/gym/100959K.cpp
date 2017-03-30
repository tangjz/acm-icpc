#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 100001;
int n;
LL mx;
struct complex {
	LL x, y; // x + y i
	void read() {
		scanf("%I64d%I64d", &x, &y);
	}
	LL mode2() const {
		return x * x + y * y;
	}
	complex operator - (complex const &t) const {
		return (complex){x - t.x, y - t.y};
	}
	complex operator * (complex const &t) const {
		return (complex){x * t.x - y * t.y, x * t.y + y * t.x};
	}
	complex conj() const {
		return (complex){x, -y};
	}
} a[maxn], tr;
complex gcd(complex u, complex v)
{
	LL len;
	for(complex w; (len = v.mode2()); u = v, v = w)
	{
		w = u * v.conj();
		w.x /= len;
		w.y /= len;
		w = u - w * v;
		complex ori = w, vec = v, tr = (complex){0, 1};
		for(int i = 0; i < 4; ++i, vec = vec * tr)
		{
			complex tmp = ori - vec;
			if(tmp.mode2() < w.mode2())
				w = tmp;
		}
	}
	return u;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		a[i].read();
	if(n == 1)
	{
		puts("0");
		return 0;
	}
	for(int i = 1; i < n; ++i)
		tr = gcd(tr, a[i] - a[i - 1]);
	LL len = tr.mode2();
	tr = tr.conj();
	for(int i = 0; i < n; ++i)
		a[i] = a[i] * tr;
	{ // calc x
		LL low = a[0].x, upp = a[0].x;
		for(int i = 1; i < n; ++i)
			if(a[i].x < low)
				low = a[i].x;
			else if(upp < a[i].x)
				upp = a[i].x;
		mx = std::max(mx, (upp - low) / len + 1);
	}
	{ // calc y
		LL low = a[0].y, upp = a[0].y;
		for(int i = 1; i < n; ++i)
			if(a[i].y < low)
				low = a[i].y;
			else if(upp < a[i].y)
				upp = a[i].y;
		mx = std::max(mx, (upp - low) / len + 1);
	}
	printf("%I64d\n", mx * mx - n);
	return 0;
}
