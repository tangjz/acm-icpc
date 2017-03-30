#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001;
int t, n, tot, que[maxn << 1 | 1];
LL s[maxn << 1 | 1];
struct Node {
	int l, r, a, b, c;
} p[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		que[tot++] = (int)0;
		que[tot++] = (int)2e9 + 10;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d%d%d", &p[i].l, &p[i].r, &p[i].a, &p[i].b, &p[i].c);
			que[tot++] = p[i].l << 1;
			que[tot++] = p[i].r << 1 | 1;
		}
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		memset(s, 0, tot * sizeof(LL));
		for(int i = 0; i < n; ++i)
		{
			s[0] += p[i].c;
			s[lower_bound(que, que + tot, p[i].l << 1) - que] += p[i].a - p[i].c;
			s[lower_bound(que, que + tot, p[i].r << 1 | 1) - que] += p[i].b - p[i].a;
		}
		LL ans = s[0];
		for(int i = 1; i < tot - 1; ++i)
		{
			s[i] += s[i - 1];
			if(ans < s[i])
				ans = s[i];
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
