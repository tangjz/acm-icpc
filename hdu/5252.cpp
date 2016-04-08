#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50010;
const long long INF = ~0ull >> 2;
struct Event
{
	long long x, y, ti;
	bool operator < (const Event &p) const
	{
		return ti < p.ti;
	}
} a[maxn];
int t, n;
long long L, R, M;
bool check(long long lim)
{
	long long amin = -INF, amax = INF, bmin = -INF, bmax = INF, tnow = a[0].ti;
	for(int i = 0; i < n; ++i)
	{
		if(a[i].ti > tnow)
		{
			amin -= a[i].ti - tnow;
			amax += a[i].ti - tnow;
			bmin -= a[i].ti - tnow;
			bmax += a[i].ti - tnow;
			tnow = a[i].ti;
		}
		amin = max(amin, a[i].x - a[i].y - lim);
		amax = min(amax, a[i].x - a[i].y + lim);
		bmin = max(bmin, a[i].x + a[i].y - lim);
		bmax = min(bmax, a[i].x + a[i].y + lim);
		if(amin > amax || bmin > bmax)
			return 0;
	}
	return amin <= amax && bmin <= bmax;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%I64d%I64d%I64d", &a[i].x, &a[i].y, &a[i].ti);
			a[i].x <<= 1;
			a[i].y <<= 1;
			a[i].ti <<= 1;
		}
		sort(a, a + n);
		L = 0, R = INF;
		while(L < R)
		{
			M = L + R >> 1;
			if(check(M))
				R = M;
			else
				L = M + 1;
		}
		if(L & 1)
			printf("%I64d/2\n", L);
		else
			printf("%I64d/1\n", L / 2);
	}
	return 0;
}
