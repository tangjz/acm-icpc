#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 131072;
int n, m, a[maxn], b[maxn];
long long k;
long long cnt(long long x)
{
	long long res = 0;
	for(int i = 1; i <= n; ++i)
	{
		int L = 0, R = m, M;
		while(L < R)
		{
			M = L + R + 1 >> 1;
			if((long long)a[i] * b[M] < x)
				R = M - 1;
			else
				L = M;
		}
		res += L;
	}
	return res;
}
int main()
{
	while(scanf("%d%d%lld", &n, &m, &k) == 3)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= m; ++i)
			scanf("%d", b + i);
		sort(b + 1, b + m + 1, greater<int>());
		b[0] = maxn;
		long long l = 1, r = 1e10, mid;
		while(l < r)
		{
			mid = l + r + 1 >> 1;
			if(cnt(mid) < k)
				r = mid - 1;
			else
				l = mid;
		}
		printf("%lld\n", l);
	}
	return 0;
}
