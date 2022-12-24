#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int t, n, m, a[maxn], l[maxn], r[maxn], ans[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(ans, 0x7f, sizeof ans);
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			l[i] = r[i] = i;
		}
		for(int i = 1; i <= n; ++i)
			while(l[i] > 1 && a[i] >= a[l[i] - 1])
				l[i] = l[l[i] - 1];
		for(int i = n; i; --i)
			while(r[i] < n && a[i] >= a[r[i] + 1])
				r[i] = r[r[i] + 1];
		for(int i = 1; i <= n; ++i)
			ans[r[i] - l[i] + 1] = min(ans[r[i] - l[i] + 1], a[i]);
		for(int i = n - 1; i; --i)
			ans[i] = min(ans[i], ans[i + 1]);
		scanf("%d", &m);
		while(m--)
		{
			int l;
			scanf("%d", &l);
			printf("%d ", ans[l]);
		}
		putchar('\n');
	}
	return 0;
}
