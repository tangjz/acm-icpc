#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 500002;
int n, q, sz, tot, fir[maxn];
LL a[maxn], b[maxn], d[maxn];
int main()
{
	scanf("%d%d", &n, &q);
	sz = (int)ceil(sqrt(n));
	for(int i = 1; i <= n; ++i)
		scanf("%I64d", a + i);
	memcpy(b + 1, a + 1, n * sizeof(LL));
	for(int i = 1; i <= n; i += sz)
		fir[tot++] = i;
	fir[tot] = n + 1;
	fir[tot + 1] = n + 2;
	for(int i = 0; i < tot; ++i)
		std::sort(b + fir[i], b + fir[i + 1]);
	while(q--)
	{
		int typ, l, r, x;
		scanf("%d", &typ);
		if(typ == 1)
		{
			scanf("%d%d%d", &l, &r, &x);
			int L = std::lower_bound(fir, fir + tot + 1, l) - fir, R = std::upper_bound(fir, fir + tot + 2, r + 1) - fir - 1;
			if(L <= R)
			{
				if(l < fir[L])
				{
					for(int i = l; i < fir[L]; ++i)
						a[i] += x;
					memcpy(b + fir[L - 1], a + fir[L - 1], (fir[L] - fir[L - 1]) * sizeof(LL));
					std::sort(b + fir[L - 1], b + fir[L]);
				}
				for(int i = L; i < R; ++i)
					d[i] += x;
				if(fir[R] <= r)
				{
					for(int i = fir[R]; i <= r; ++i)
						a[i] += x;
					memcpy(b + fir[R], a + fir[R], (fir[R + 1] - fir[R]) * sizeof(LL));
					std::sort(b + fir[R], b + fir[R + 1]);
				}
			}
			else
			{
				if(l < fir[L])
					--L;
				for(int i = l; i <= r; ++i)
					a[i] += x;
				memcpy(b + fir[L], a + fir[L], (fir[L + 1] - fir[L]) * sizeof(LL));
				std::sort(b + fir[L], b + fir[L + 1]);
			}
		}
		else
		{
			int L = 0, R = -1;
			scanf("%d", &x);
			for(int i = 0; i < tot; ++i)
				if(*std::lower_bound(b + fir[i], b + fir[i + 1], x - d[i]) == x - d[i])
				{
					for(int j = fir[i]; j < fir[i + 1]; ++j)
						if(a[j] == x - d[i])
						{
							L = j;
							break;
						}
					break;
				}
			for(int i = tot - 1; i >= 0; --i)
				if(*std::lower_bound(b + fir[i], b + fir[i + 1], x - d[i]) == x - d[i])
				{
					for(int j = fir[i + 1] - 1; j >= fir[i]; --j)
						if(a[j] == x - d[i])
						{
							R = j;
							break;
						}
					break;
				}
			printf("%d\n", R - L);
		}
	}
	return 0;
}
