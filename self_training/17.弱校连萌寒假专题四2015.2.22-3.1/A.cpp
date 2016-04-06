#include <cstdio>
const int maxn = 100001;
int n, m, a[maxn];
bool check(int lim)
{
	int ret = 0, sum = 0;
	for(int i = 0; i < n; ++i)
		if(sum < a[i])
		{
			++ret;
			sum = lim - a[i];
		}
		else
			sum -= a[i];
	return ret <= m;
}
int main()
{
	int l = 0, r = 0, mid;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		if(l < a[i])
			l = a[i];
		r += a[i];
	}
	while(l < r)
	{
		mid = l + r >> 1;
		if(check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
