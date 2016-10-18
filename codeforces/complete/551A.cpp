#include <stdio.h>
const int maxn = 2002;
int n, a[maxn], c[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		++c[a[i]];
	}
	for(int i = maxn - 2; i >= 1; --i)
		c[i] += c[i + 1];
	for(int i = 1; i <= n; ++i)
		printf("%d%c", c[a[i] + 1] + 1, " \n"[i == n]);
	return 0;
}
