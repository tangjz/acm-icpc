#include <cstdio>
const int maxn = 200001;
int n, p[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		p[x] = i;
	}
	p[0] = n + 1;
	for(int i = 1; i <= n; ++i)
		ans += p[i - 1] > p[i];
	printf("%d\n", ans);
	return 0;
}
