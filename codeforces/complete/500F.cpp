#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 4001, maxv = 4001, maxt = 20001;
int n, p, f[maxn][maxv], g[maxn][maxv], q, ans;
struct Node
{
	int c, h, t;
	bool operator < (const Node &x) const
	{
		return t < x.t;
	}
} s[maxn];
const int &max(const int &a, const int &b)
{
	return a < b ? b : a;
}
int main()
{
	scanf("%d%d", &n, &p);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d%d", &s[i].c, &s[i].h, &s[i].t);
	sort(s + 1, s + n + 1);
	for(int i = 1, j = 1; (i - 1) * p + 1 < maxt; ++i)
	{
		for( ; j <= n && s[j].t <= i * p; ++j)//dp : left to right
			if(j > 1 && (i - 1) * p < s[j - 1].t)
			{
				for(int k = 0; k < s[j].c; ++k)
					f[j][k] = f[j - 1][k];
				for(int k = s[j].c; k < maxv; ++k)
					f[j][k] = max(f[j - 1][k], f[j - 1][k - s[j].c] + s[j].h);
			}
			else
				for(int k = s[j].c; k < maxv; ++k)
					f[j][k] = s[j].h;
		int tmp = j;
		for(--j; j > 0 && (i - 1) * p < s[j].t; --j)//dp : right to left
			if(j < n && s[j + 1].t <= i * p)
			{
				for(int k = 0; k < s[j].c; ++k)
					g[j][k] = g[j + 1][k];
				for(int k = s[j].c; k < maxv; ++k)
					g[j][k] = max(g[j + 1][k], g[j + 1][k - s[j].c] + s[j].h);
			}
			else
				for(int k = s[j].c; k < maxv; ++k)
					g[j][k] = s[j].h;
		j = tmp;
	}
	scanf("%d", &q);
	while(q--)
	{
		int l, r, m, pl = n + 1, pr = 0, c;
		scanf("%d%d", &r, &c);
		l = r - p + 1;
		m = (r - 1) / p * p;
		for(int i = 1; i <= n; ++i)
			if(l <= s[i].t)
			{
				pl = i;
				break;
			}
		for(int i = n; i > 0; --i)
			if(s[i].t <= r)
			{
				pr = i;
				break;
			}
		if(pl > pr)//nothing
		{
			puts("0");
			continue;
		}
		ans = 0;
		if(m < s[pl].t)
			ans = f[pr][c];
		else if(s[pr].t <= m)
			ans = g[pl][c];
		else//two consecutive squares
			for(int i = 0; i <= c; ++i)
				if(ans < f[pr][i] + g[pl][c - i])
					ans = f[pr][i] + g[pl][c - i];
		printf("%d\n", ans);
	}
	return 0;
}
