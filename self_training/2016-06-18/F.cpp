#include <cstdio>
typedef long long LL;
const int maxm = 10001, maxd = 64;
int t, m, tot, ans[maxm * maxd];
LL n, a[maxm];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld%d", &n, a + 0, &m);
		--a[0];
		tot = 0;
		for(int i = 1; i <= m; ++i)
		{
			scanf("%lld", a + i);
			--a[i];
		}
		for(int i = 1; i <= m; ++i)
		{
			LL u = a[i - 1], v = a[i], w;
			static int d, seq[maxd];
			for(d = 0; ; ++d, u = (u << 1) % (n << 1))
			{
				w = v - u;
				if(w < 0)
					w += n << 1;
				if(w < 1LL << d)
					break;
			}
			for(int j = 0; j < d; seq[j++] = w & 1, w >>= 1);
			for(u = a[i - 1]; d--; )
			{
				ans[tot++] = (u < n) == (seq[d] == 1);
				u = ((u << 1) + seq[d]) % (n << 1);
			}
		}
		printf("%d:", tot);
		for(int i = 0; i < tot; ++i)
			putchar(ans[i] ? 'L' : 'R');
		putchar('\n');
	}
	return 0;
}
