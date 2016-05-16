#include <stdio.h>
const int maxn = 601;
int n, m, f[maxn + 1], stack[maxn][2], top, ans[maxn][maxn];
char str[maxn + 1];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", str + 1);
		for(int j = 1, w, h; j <= m + 1; ++j)
		{
			str[j] == '1' ? ++f[j] : (f[j] = 0);
			for(w = 0; top > 0 && stack[top][1] > f[j]; --top)
			{
				w += stack[top][0];
				h = stack[top - 1][1] < f[j] ? f[j] : stack[top - 1][1];
				++ans[stack[top][1]][w];
				--ans[h][w];
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
			ans[i - 1][j] += ans[i][j];
		for(int j = m; j > 0; --j)
			ans[i][j - 1] += ans[i][j];
		for(int j = m; j > 0; --j)
			ans[i][j - 1] += ans[i][j];
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			printf("%d%c", ans[i][j], " \n"[j == m]);
	return 0;
}
