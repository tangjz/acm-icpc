#include <stdio.h>
#include <algorithm>
const int maxn = 10000;
int n, a[maxn + 1];
short f[maxn][maxn], ans;
void upd(short &x, short y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	std::sort(a, a + n);
	a[n] = ~0u >> 1;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1, k = i + 2; j < n; ++j)
		{
			upd(f[i][j], 2);
			for( ; a[j] - a[i] > a[k] - a[j]; ++k);
			if(a[j] - a[i] == a[k] - a[j])
				upd(f[j][k], f[i][j] + 1);
			upd(ans, f[i][j]);
		}
	printf("%d\n", (int)ans);
	return 0;
}
