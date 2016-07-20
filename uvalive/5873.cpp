#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001;
int t, n, tot, p, q, x[maxn], y[maxn], row[maxn], col[maxn], que[maxn], systim, tim[maxn];
bool vis[maxn];
std::pair<int, std::pair<int, int> > a[maxn << 1];
void solve(int n, int x[], int y[], int m, int line[])
{
	int totx = 0;
	for(int i = 0; i < n; ++i)
		que[totx++] = x[i];
	std::sort(que, que + totx);
	totx = std::unique(que, que + totx) - que;
	tot = 0;
	for(int i = 0; i < n; ++i)
		a[tot++] = std::make_pair(y[i], std::make_pair(std::lower_bound(que, que + totx, x[i]) - que, i));
	for(int i = 0; i < m; ++i)
		a[tot++] = make_pair(line[i], std::make_pair(-1, -1));
	std::sort(a, a + tot);
	for(int i = 0, o = 0; i < tot; ++i)
	{
		int val = a[i].first, idx = a[i].second.first;
		if(idx < 0)
		{
			o = 1;
			a[i].second = std::make_pair(maxn, maxn);
			++systim;
		}
		else if(o && tim[idx] != systim)
		{
			vis[a[i].second.second] = 1;
			tim[idx] = systim;
		}
	}
	std::sort(a, a + tot);
	for(int i = tot - 1, o = 0; i >= 0; --i)
	{
		int val = a[i].first, idx = a[i].second.first;
		if(idx < 0)
		{
			o = 1;
			++systim;
		}
		else if(o && tim[idx] != systim)
		{
			vis[a[i].second.second] = 1;
			tim[idx] = systim;
		}
	}
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &tot);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", x + i, y + i);
		p = q = 0;
		while(tot--)
		{
			int x;
			char op[2];
			scanf("%s%d", op, &x);
			(op[0] == 'H' ? row[p++] : col[q++]) = x;
		}
		memset(vis, 0, n * sizeof(bool));
		solve(n, x, y, p, row);
		solve(n, y, x, q, col);
		tot = 0;
		for(int i = 0; i < n; ++i)
			if(vis[i])
				++tot;
		// printf("%d\n", tot);
		puts(tot * 5 >= 3 * n ? "PASSED" : "FAILED");
	}
	return 0;
}
