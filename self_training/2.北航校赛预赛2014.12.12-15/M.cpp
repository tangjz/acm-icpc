#include <cstdio>
const int maxn = 100010;
int n, k, h[maxn], ans;
int main()
{
	while(scanf("%d%d", &n, &k) == 2)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d", h + i);
		ans = 0;
		for(int i = 1; i < n; ++i)
			if(h[i] != h[i + 1])
				++ans;
		printf("%d\n", ans * k);
	}
	return 0;
}
