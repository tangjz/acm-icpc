#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 1001, mod = 1000000007;
int ans;
void calc(int n, int m, char str[maxn + 1][maxn + 1])
{
	int top, sum;
	static int h[maxn][maxn] = {}, hh[maxn], no[maxn], s[maxn][maxn] = {};
	for(int i = 1; i <= n; ++i)
	{
		top = 0;
		no[top] = 0;
		sum = 0;
		for(int j = 1; j <= m; ++j)
		{
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
			if(s[i][j] >= mod)
				s[i][j] -= mod;
			else if(s[i][j] < 0)
				s[i][j] += mod;
			if(str[i][j] == '1')
				h[i][j] = h[i - 1][j] + 1;
			else
			{
				h[i][j] = 0;
				top = 0;
				no[top] = j;
				sum = 0;
				continue;
			}
			while(top > 0 && h[i][j] <= hh[top])
			{
				sum -= hh[top] * (no[top] - no[top - 1]);
				--top;
			}
			hh[++top] = h[i][j];
			no[top] = j;
			sum += hh[top] * (no[top] - no[top - 1]);
			if((s[i][j] += sum) >= mod)
				s[i][j] -= mod;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		top = 0;
		no[top] = 0;
		sum = 0;
		for(int j = 1; j <= m; ++j)
		{
			if(str[n - i + 1][m - j + 1] == '1')
				h[i][j] = h[i - 1][j] + 1;
			else
			{
				h[i][j] = 0;
				top = 0;
				no[top] = j;
				sum = 0;
				continue;
			}
			while(top > 0 && h[i][j] <= hh[top])
			{
				sum -= hh[top] * (no[top] - no[top - 1]);
				--top;
			}
			hh[++top] = h[i][j];
			no[top] = j;
			sum += hh[top] * (no[top] - no[top - 1]);
			ans = (ans + (LL)sum * (s[n - i][m - j] - s[n][m - j])) % mod;
		}
	}
}
int n, m, f[maxn + 1], stack[maxn][2], top, g[maxn][maxn];
char str[maxn][maxn + 1], buf[maxn][maxn + 1];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", str[i] + 1);
		for(int j = 1, w, h; j <= m + 1; ++j)
		{
			str[i][j] == '1' ? ++f[j] : (f[j] = 0);
			for(w = 0; top > 0 && stack[top][1] > f[j]; --top)
			{
				w += stack[top][0];
				h = stack[top - 1][1] < f[j] ? f[j] : stack[top - 1][1];
				++g[stack[top][1]][w];
				--g[h][w];
			}
			if(!top || stack[top][1] < f[j])
			{
				stack[++top][0] = w + 1;
				stack[top][1] = f[j];
			}
			else
				stack[top][0] += w + 1;
		}
	}
	for(int i = n; i > 0; --i)
	{
		for(int j = m; j > 0; --j)
			g[i - 1][j] += g[i][j];
		for(int j = m; j > 0; --j)
			g[i][j - 1] += g[i][j];
		for(int j = m; j > 0; --j)
			g[i][j - 1] += g[i][j];
	}
	int all = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			if((all += g[i][j]) >= mod)
				all -= mod;
			ans = (ans - (i * (i + 1LL) >> 1) * (j * (j + 1LL) >> 1) % mod * g[i][j]) % mod;
		}
	ans = (ans + (all * (all + 1LL) >> 1)) % mod;
	calc(n, m, str);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			buf[m - j + 1][i] = str[i][j];
	calc(m, n, buf);
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
