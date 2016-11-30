#include <stdio.h>
#include <algorithm>
using namespace std;
#define x first
#define y second
typedef long long LL;
const int maxn = 200001;
int n, tot, que[maxn], mx, bit[maxn];
pair<int, int> a[maxn];
LL ans;
void add(int x, int v)
{
	for( ; x <= tot; x += x & -x)
		bit[x] += v;
}
int find(int k)
{
	int x = 0;
	for(int y = mx; y; y >>= 1)
	{
		int z = x | y;
		if(z < tot && bit[z] < k)
		{
			x = z;
			k -= bit[z];
		}
	}
	return x + 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n << 1; ++i)
	{
		scanf("%d%d", &a[i].x, &a[i].y);
		if(a[i].x > a[i].y)
			swap(a[i].x, a[i].y);
		que[tot++] = a[i].y;
	}
	sort(a, a + (n << 1));
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(mx = 1; mx < tot; mx <<= 1);
	mx >>= 1;
	for(int i = 1; i < n << 1; ++i)
	{
		int id = lower_bound(que, que + tot, a[i].y) - que + 1;
		++bit[id];
	}
	for(int i = 1; i <= tot; ++i)
	{
		int j = i + (i & -i);
		if(j <= tot)
			bit[j] += bit[i];
	}
	int amin = a[0].x, amax = a[0].y, tmp0, tmp1;
	for(int i = 1; i <= n; ++i)
	{
		add(lower_bound(que, que + tot, a[i].y) - que + 1, -1);
		tmp0 = que[find(1) - 1];
		tmp1 = que[find(n) - 1];
		ans = max(ans, (LL)amin * min(amax, tmp1) + (LL)a[i].x * min(a[i].y, tmp0));
		if(i == n)
			tmp0 = ~0u >> 1;
		tmp1 = que[find(n - i + 1) - 1];
		ans = max(ans, (LL)amin * min(amax, tmp0) + (LL)a[i].x * min(a[i].y, tmp1));
		amax = min(amax, a[i].y);
	}
	printf("%lld\n", ans);
	return 0;
}
