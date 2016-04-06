#include <cstdio>
const long long INF = 1.25e10;
int t, n;
long long m;
inline long long val(int i, int j)
{
	return (long long)i * (i + j + 100000) - (long long)j * (100000 - j);
}
long long cnt(long long lim)
{
	long long ret = 0;
	for(int j = 1; j <= n; ++j)
	{
		int l = 0, r = n, mid;
		while(l < r)
		{
			mid = l + r + 1 >> 1;
			if(val(mid, j) <= lim)
				l = mid;
			else
				r = mid - 1;
		}
		ret += l;
	}
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		long long l = -INF, r = INF, mid;
		scanf("%d%lld", &n, &m);
		while(l < r)
		{
			mid = l + r >> 1;
			if(cnt(mid) < m)
				l = mid + 1;
			else
				r = mid;
		}
		printf("%lld\n", l);
	}
	return 0;
}
