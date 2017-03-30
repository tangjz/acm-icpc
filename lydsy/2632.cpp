#include <stdio.h>
const int maxn = 10001;
int n, tot, pr[maxn], d[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	for(int i = 0, j = tot - 1; i <= j; --j, ++ans)
		for(int val = pr[j]; i < j && val * pr[i] <= n; val *= pr[i++]);
	printf("%d\n", ans);
	return 0;
}
