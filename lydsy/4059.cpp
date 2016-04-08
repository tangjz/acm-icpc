#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int t, n, val[maxn], tot, que[maxn], pos[maxn], l[maxn], r[maxn];
bool boring(int L, int R)
{
	if(L >= R)
		return 0;
	for(int i = L, j = R; i <= j; ++i, --j)
	{
		if(l[i] < L && r[i] > R)
			return boring(L, i - 1) || boring(i + 1, R);
		if(l[j] < L && r[j] > R)
			return boring(L, j - 1) || boring(j + 1, R);
	}
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", val + i);
			que[tot++] = val[i];
		}
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		memset(pos, 0, tot * sizeof(int));
		for(int i = 1; i <= n; ++i)
		{
			val[i] = lower_bound(que, que + tot, val[i]) - que;
			l[i] = pos[val[i]];
			pos[val[i]] = i;
		}
		memset(pos, 0, tot * sizeof(int));
		for(int i = n; i; --i)
		{
			r[i] = pos[val[i]] ? pos[val[i]] : n + 1;
			pos[val[i]] = i;
		}
		puts(boring(1, n) ? "boring" : "non-boring");
	}
	return 0;
}
