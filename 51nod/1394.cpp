#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, q, a[maxn], typ[maxn], b[maxn], tot, que[maxn << 1], cnt[maxn << 1];
LL sum[maxn << 1], ans;
template<class T> void bit_add(T bit[], int x, int v)
{
	for( ; x < tot; x += ~x & x + 1)
		bit[x] += v;
}
template<class T> T bit_sum(T bit[], int x)
{
	T ret = 0;
	for( ; x >= 0; x -= ~x & x + 1)
		ret += bit[x];
	return ret;
}
void add(int val)
{
	int pos = lower_bound(que, que + tot, val) - que;
	int ca = bit_sum(cnt, pos), cb = bit_sum(cnt, tot - 1) - ca;
	LL sa = bit_sum(sum, pos), sb = bit_sum(sum, tot - 1) - sa;
	ans += (LL)ca * val - sa + sb - (LL)cb * val;
	bit_add(cnt, pos, 1);
	bit_add(sum, pos, val);
}
bool sub(int val)
{
	int pos = lower_bound(que, que + tot, val) - que;
	int count = bit_sum(cnt, pos) - bit_sum(cnt, pos - 1);
	if(!count)
		return 0;
	bit_add(cnt, pos, -1);
	bit_add(sum, pos, -val);
	int ca = bit_sum(cnt, pos), cb = bit_sum(cnt, tot - 1) - ca;
	LL sa = bit_sum(sum, pos), sb = bit_sum(sum, tot - 1) - sa;
	ans -= (LL)ca * val - sa + sb - (LL)cb * val;
	return 1;
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		que[tot++] = a[i];
	}
	for(int i = 0; i < q; ++i)
	{
		scanf("%d", typ + i);
		if(typ[i] < 3)
		{
			scanf("%d", b + i);
			que[tot++] = b[i];
		}
	}
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 0; i < n; ++i)
		add(a[i]);
	for(int i = 0; i < q; ++i)
		if(typ[i] == 1)
			add(b[i]);
		else if(typ[i] == 2)
		{
			if(!sub(b[i]))
				puts("-1");
		}
		else
			printf("%lld\n", ans);
	return 0;
}
