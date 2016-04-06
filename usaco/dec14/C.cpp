#include <cstdio>
const int maxn = 100010;
int n, v[maxn], now = ~0u >> 1, ans;
int main()
{
	freopen("cowjog.in", "r", stdin);
	freopen("cowjog.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%*d%d", v + i);
	for(int i = n - 1; i >= 0; --i)
		if(v[i] <= now)
		{
			++ans;
			now = v[i];
		}
	printf("%d\n", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
