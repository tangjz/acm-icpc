#include <cstdio>
typedef int LL;
LL n, m, u, d, x, tmp, ans;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		ans = ~0u >> 1;
		while(m--)
		{
			scanf("%d%d", &u, &d);
			x = (n * d) / (u + d);
			tmp = (u + d) * x - n * d;
			while(tmp <= 0)
				tmp += u + d;
			if(ans > tmp)
				ans = tmp;
		}
		printf("%d\n", ans);
	}
	return 0;
}
