#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 2000001;
int n, q, a[maxn], f[maxn], g[maxn];
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	memcpy(a + n, a, n * sizeof(int));
	while(q--)
	{
		int ans = n, sp = 0;
		LL val, cst = 0;
		scanf("%I64d", &val);
		for(int i = 0, j = 0; i < n; ++i)
		{
			for( ; j < (n << 1) && cst + a[j] <= val; cst += a[j++]);
			f[i] = j - i;
			g[i] = j % n;
			cst -= a[i];
			if(f[i] < f[sp])
				sp = i;
		}
		for(int i = sp; i <= sp + f[sp]; ++i)
		{
			int cnt = 0;
			for(int len = 0, j = i % n; len < n; ++cnt, len += f[j], j = g[j]);
			if(cnt < ans)
				ans = cnt;
		}
		printf("%d\n", ans);
	}
	return 0;
}
