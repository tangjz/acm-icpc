#include <stdio.h>
#include <cstring>
const int maxn = 5000001;
int tot, pr[maxn], d[maxn];
long long ans[maxn];
int main()
{
	for(int i = 2; i + 1 < maxn; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = i;
			ans[i + 1] = 1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	for(int i = 2; i < maxn; ++i)
		for(int j = i << 1, k = i + 1; j + 1 < maxn; j += i, ++k)
			if(d[k] != k)
				ans[j + 1] = 1;
	for(int i = 3; i < maxn; ++i)
		ans[i] = ans[i - 1] + (ans[i] ? 0 : i);
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int L, R;
		scanf("%d%d", &L, &R);
		printf("%lld\n", ans[R] - ans[L - 1]);
	}
	return 0;
}
