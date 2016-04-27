#include <cstdio>
const int maxn = 1 << 21;
int t, n, m;
long long a[maxn], tmp;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &m);
		n = 1 << m;
		for(int i = 0; i < n; ++i)
			scanf("%lld", a + i);
		printf("Case #%d:", Case);
		if(n == 1)
		{
			printf(" %d\n", a[0]);
			continue;
		}
		tmp = a[n - 1];
		for(int i = 1; i < n; i <<= 1)
			for(int j = 0, k = i; j < n; j = k, k = j + i)
				for(int o = 0; o < i; ++o)
				{
					long long t = a[j];
					a[j++] += a[k];
					a[k++] -= t;
				}
		a[0] -= tmp << m - 1;
		for(int i = 0; i < n; ++i)
			printf(" %lld", a[i] >> m - 1);
		putchar('\n');
	}
	return 0;
}
