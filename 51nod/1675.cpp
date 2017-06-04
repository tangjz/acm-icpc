#include <stdio.h>
const int maxn = 100001;
int n, a[maxn], b[maxn], c[maxn];
long long f[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", b + i);
	for(int i = n; i >= 1; --i)
	{
		for(int j = i; j <= n; j += i)
			++c[a[b[j]]];
		for(int j = i; j <= n; j += i)
			f[i] += c[b[a[j]]];
		for(int j = i; j <= n; j += i)
			--c[a[b[j]]];
		for(int j = i + i; j <= n; j += i)
			f[i] -= f[j];
	}
	printf("%lld\n", f[1]);
	return 0;
}
