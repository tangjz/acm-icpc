#include <cstdio>
const int maxn = 100010;
int n, l[maxn], r[maxn], pos;
long long num[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%lld", num + i);
		l[i] = r[i] = i;
	}
	for(int i = 2; i <= n; ++i)
		while(l[i] > 1 && num[l[i] - 1] >= num[i])
			l[i] = l[l[i] - 1];
	for(int i = n - 1; i > 0; --i)
		while(r[i] < n && num[r[i] + 1] >= num[i])
			r[i] = r[r[i] + 1];
	for(int i = 2; i <= n; ++i)
		num[i] += num[i - 1];
	ans = -1;
	for(int i = 1; i <= n; ++i)
		if(ans < (num[i] - num[i - 1]) * (num[r[i]] - num[l[i] - 1]))
		{
			ans = (num[i] - num[i - 1]) * (num[r[i]] - num[l[i] - 1]);
			pos = i;
		}
	printf("%lld\n%d %d\n", ans, l[pos], r[pos]);
	return 0;
}