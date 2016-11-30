#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001, maxm = 1001;
int n, m, p, x[maxn], y[maxn], f[2][maxm], ans;
struct PP
{
	int pos, low, high;
	bool operator < (const PP &t) const
	{
		return pos < t.pos;
	}
} a[maxn];
void upd(int &x, int y)
{
	if(x == -1 || x > y)
		x = y;
}
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", x + i, y + i);
	for(int i = 0; i < p; ++i)
		scanf("%d%d%d", &a[i].pos, &a[i].low, &a[i].high);
	sort(a, a + p);
	for(int i = 0, j = 0, cur = 0, nxt = 1; i < n; ++i, cur ^= 1, nxt ^= 1)
	{
		memset(f[nxt], -1, sizeof f[nxt]);
		for(int k = 1; k <= m; ++k)
			if(f[cur][k] != -1)
				upd(f[nxt][min(k + x[i], m)], f[cur][k] + 1);
		for(int k = 1; k <= m; ++k)
			if(f[nxt][k] != -1)
				upd(f[nxt][min(k + x[i], m)], f[nxt][k] + 1);
		for(int k = y[i] + 1; k <= m; ++k)
			if(f[cur][k] != -1)
				upd(f[nxt][k - y[i]], f[cur][k]);
		if(i + 1 == a[j].pos)
		{
			bool flag = 0;
			for(int k = a[j].low + 1; k < a[j].high; ++k)
				if(f[nxt][k] != -1)
				{
					flag = 1;
					break;
				}
			if(!flag)
				break;
			for(int k = 1; k <= a[j].low; ++k)
				f[nxt][k] = -1;
			for(int k = a[j].high; k <= m; ++k)
				f[nxt][k] = -1;
			ans = ++j;
		}
	}
	if(ans < p)
		puts("0");
	else
	{
		puts("1");
		ans = ~0u >> 1;
		for(int i = 1; i <= m; ++i)
			if(f[n & 1][i] != -1 && ans > f[n & 1][i])
				ans = f[n & 1][i];
	}
	printf("%d\n", ans);
	return 0;
}
