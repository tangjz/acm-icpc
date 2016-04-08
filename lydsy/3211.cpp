/*
 * 大数直接暴力修改 小数利用并查集快速跳过 
 */
#include <cmath>
#include <cstdio>
const int maxn = 1 << 17;
int n, m, data[maxn], fa[maxn];
long long s[maxn];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void add(int x, int val) { for( ; x <= n; x += x & -x) s[x] += val; }
inline long long sum(int x) { long long ret = 0; for( ; x; x -= x & -x) ret += s[x]; return ret; }
int main()
{
	int x, l, r;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &data[i]);
		add(i, data[i]);
		fa[i] = data[i] > 1 ? i : i + 1;
	}
	fa[n + 1] = n + 1;
	scanf("%d", &m);
	while(m--)
	{
		scanf("%d%d%d", &x, &l, &r);
		if(x == 1) printf("%lld\n", sum(r) - sum(l - 1));
		else
			for(l = find(l); l <= r; l = find(l + 1))
			{
				x = (int)sqrt(data[l]);
				add(l, x - data[l]);
				data[l] = x;
				if(data[l] == 1) fa[l] = l + 1;
			}
	}
	return 0;
}
