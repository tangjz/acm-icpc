#include <cstdio>
#include <algorithm>
const int maxn = 100001;
int n, a[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	for(int i = n - 2, j = a[n] - a[n - 1]; i >= 0; --i)
	{
		if(a[i] > j)
		{
			puts("YES");
			return 0;
		}
		j = std::min(j, a[i + 1] - a[i]);
	}
	puts("NO");
	return 0;
}
