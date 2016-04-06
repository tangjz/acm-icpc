#include <cstdio>
const int maxn = 1001;
int t, n, a[maxn], sg;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		sg = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = n - 1; i >= 0; i -= 2)
			sg ^= a[i + 1] - a[i];
		puts(sg ? "TAK" : "NIE");
	}
	return 0;
}
