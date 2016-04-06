#include <cstdio>
const int maxn = 500001;
int n, a[maxn << 1];
long long cnt, ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		a[n + i] = a[i];
		cnt += a[i];
	}
	long long k = cnt;
	for(int i = n, j = 0; i < n << 1; ++i)
	{
		while(j < i && k > cnt >> 1)
			k -= a[j++];
		if(ans < k)
			ans = k;
		k += a[i];
	}
	printf("%lld\n", ans);
	return 0;
}
