#include <stdio.h>
#include <algorithm>
#include <functional>
const int maxn = 50001;
int n, a[maxn], L[maxn], R[maxn], mx, f[maxn], g[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
	{
		L[i] = std::lower_bound(f + 1, f + mx + 1, a[i]) - f;
		f[L[i]] = a[i];
		if(mx < L[i])
			mx = L[i];
	}
	mx = 0;
	for(int i = n; i >= 1; --i)
	{
		R[i] = std::lower_bound(f + 1, f + mx + 1, a[i], std::greater<int>()) - f;
		f[R[i]] = a[i];
		if(mx < R[i])
			mx = R[i];
	}
	for(int i = 1; i <= n; ++i)
		if(L[i] + R[i] - 1 == mx)
			++g[L[i]];
	printf("A:");
	for(int i = 1; i <= n; ++i)
		if(L[i] + R[i] - 1 == mx && g[L[i]] > 1)
			printf("%d ", i);
	putchar('\n');
	printf("B:");
	for(int i = 1; i <= n; ++i)
		if(L[i] + R[i] - 1 == mx && g[L[i]] == 1)
			printf("%d ", i);
	putchar('\n');
	return 0;
}
