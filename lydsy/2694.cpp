#include <stdio.h>
#include <algorithm>
const int maxn = 4000001;
int tot, pr[maxn >> 3 | 1], d[maxn], f[maxn];
inline int sum2(int x)
{
	return (x * (x + 1)) >> 1;
}
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = i;
			f[i] = 1 - i;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				f[k] = d[i / pr[j]] == pr[j] ? 0 : f[i] - f[i / pr[j]];
				break;
			}
			else
				f[k] = f[i] * f[pr[j]];
		}
	}
	for(int i = 2; i < maxn; ++i)
		f[i] = f[i - 1] + i * f[i];
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int n, m, ans = 0;
		scanf("%d%d", &n, &m);
		if(n > m)
			std::swap(n, m);
		for(int i = 1, j; i <= n; i = j + 1) // [i, j]
		{
			j = std::min(n / (n / i), m / (m / i));
			ans += (f[j] - f[i - 1]) * sum2(n / i) * sum2(m / i);
		}
		printf("%d\n", ans & ((1 << 30) - 1));
	}
	return 0;
}
