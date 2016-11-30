#include <cstdio>
const int maxn = 101;
int n, a[maxn], b[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", a + i, b + i);
	ans = n;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(i != j && a[i] == b[j])
			{
				--ans;
				break;
			}
	printf("%d\n", ans);
	return 0;
}
