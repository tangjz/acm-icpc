#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 100001;
int n, q, a[maxn], que[maxn], r, L[maxn], R[maxn], id[maxn], last[maxm];
long long ans[maxm];
bool cmp(const int &x, const int &y)
{
	return a[x] < a[y] || a[x] == a[y] && x < y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		id[i] = i;
		while(r > 0 && a[que[r - 1]] <= a[i])
			--r;
		L[i] = r ? que[r - 1] + 1 : 0;
		que[r++] = i;
	}
	r = 0;
	for(int i = n - 1; i >= 0; --i)
	{
		while(r > 0 && a[que[r - 1]] <= a[i])
			--r;
		R[i] = r ? que[r - 1] - 1 : n - 1;
		que[r++] = i;
	}
	sort(id, id + n, cmp);
	for(int i = 0; i < n; ++i)
	{
		ans[a[id[i]]] += (R[id[i]] - id[i] + 1LL) * (id[i] - max(last[a[id[i]]], L[id[i]]) + 1LL);
		last[a[id[i]]] = id[i] + 1;
	}
	for(int i = maxm - 2; i >= 0; --i)
		ans[i] += ans[i + 1];
	scanf("%d", &q);
	while(q-- > 0)
	{
		int k;
		scanf("%d", &k);
		printf("%lld\n", k < maxm ? ans[k] : 0);
	}
	return 0;
}
