#include <stdio.h>
#include <algorithm>
const int maxn = 1000002;
int n, a[maxn], L[maxn], R[maxn], idx, que[maxn], ord[maxn], bit[maxn];
long long ans;
void upd(int x, int v)
{
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
bool cmp(const int &x, const int &y)
{
	return L[x] < L[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		ord[i] = i;
	}
	a[0] = maxn;
	que[idx = 0] = 0;
	for(int i = 1; i <= n; ++i)
	{
		for( ; a[que[idx]] <= a[i]; --idx);
		L[i] = que[idx] + 1;
		que[++idx] = i;
	}
	a[n + 1] = 0;
	que[idx = 0] = n + 1;
	for(int i = n; i >= 1; --i)
	{
		for( ; a[que[idx]] >= a[i]; --idx);
		R[i] = que[idx] - 1;
		que[++idx] = i;
	}
	std::sort(ord + 1, ord + n + 1, cmp);
	for(int i = 1, j = 1; i <= n; ++i)
	{
		for( ; j <= n && L[ord[j]] <= i; ++j)
			upd(ord[j], 1);
		ans += sum(R[i]) - sum(i - 1);
	}
	printf("%lld\n", ans);
	return 0;
}
