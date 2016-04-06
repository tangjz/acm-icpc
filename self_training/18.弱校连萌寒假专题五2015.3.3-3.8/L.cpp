#include <cstdio>
#include <cstring>
const int maxn = 65, maxm = 66;
int t, n, m, f[maxn][maxm], g[maxn][maxm], stack[maxm][maxn], l[maxm + 1], r[maxm + 1], ans;
void move(int n, int m, int f, int t)
{
	if(n == 1)
	{
		printf("move %d from %d to %d", stack[f][stack[f][0]], f, t);
		if(stack[t][0])
			printf(" atop %d", stack[t][stack[t][0]]);
		putchar('\n');
		stack[t][++stack[t][0]] = stack[f][stack[f][0]--];
		return;
	}
	int tmp = r[0];
	while(tmp == f || tmp == t)
		tmp = r[tmp];
	move(g[n][m], m, f, tmp);
	l[r[tmp]] = l[tmp];
	r[l[tmp]] = r[tmp];
	move(n - g[n][m], m - 1, f, t);
	l[r[tmp]] = tmp;
	r[l[tmp]] = tmp;
	move(g[n][m], m, tmp, t);
}
int main()
{
	memset(f, 0x0f, sizeof f);
	for(int i = 1; i < maxm; ++i)
		f[1][i] = 1;
	for(int i = 2; i < maxn; ++i)
		for(int j = 3; j < maxm; ++j)
			for(int k = 1; k < i; ++k)
				if(f[i][j] > f[i - k][j - 1] + f[k][j] * 2)
				{
					f[i][j] = f[i - k][j - 1] + f[k][j] * 2;
					g[i][j] = k;
				}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", f[n][m]);
		memset(stack, 0, sizeof stack);
		l[m + 1] = m;
		r[0] = 1;
		for(int i = 1; i <= m; ++i)
		{
			l[i] = i - 1;
			r[i] = i + 1;
		}
		for(int i = n; i > 0; --i)
			stack[1][++stack[1][0]] = i;
		move(n, m, 1, m);
	}
	return 0;
}
