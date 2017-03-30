#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 3001, maxm = 11;
int n, m, a[maxn];
LL s[maxn], f[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
	{
		s[i] = s[i - 1] + a[i];
		f[i] = s[i] - (s[(i + 1) >> 1] << 1) + ((i + 1) & 1 ? 0 : a[(i + 1) >> 1]);
	}
	for(int i = 2; i <= m; ++i)
		for(int j = n; j >= 1; --j)
			for(int k = j; k >= 1; --k)
			{
				LL tmp = f[k - 1] + s[j] + s[k - 1] - (s[(j + k) >> 1] << 1) + ((j + k) & 1 ? 0 : a[(j + k) >> 1]);
				if(f[j] > tmp)
					f[j] = tmp;
			}
	printf("%lld\n", f[n]);
	return 0;
}
