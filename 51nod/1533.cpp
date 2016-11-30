#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int n, a[maxn], ord[maxn], bit[maxn], ans[maxn];
void add(int x, int v)
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
	return a[x] < a[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		ord[i] = i;
	}
	sort(ord + 1, ord + n + 1, cmp);
	for(int i = 1, j; i <= n; i = j)
	{
		for(j = i; j <= n && a[ord[i]] == a[ord[j]]; ++j)
			for(int k = 1; k < n && k * (ord[j] - 1) + 2 <= n; ++k)
				ans[k] += sum(min(k * ord[j] + 1, n)) - sum(k * (ord[j] - 1) + 1);
		for(j = i; j <= n && a[ord[i]] == a[ord[j]]; ++j)
			add(ord[j], 1);
	}
	for(int i = 1; i < n; ++i)
		printf("%d%c", ans[i], " \n"[i == n - 1]);
	return 0;
}
