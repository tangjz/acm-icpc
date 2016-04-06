#include <cstdio>
const int maxn = 100010;
int n, x[maxn], y[maxn], f[maxn][2];
int abs(int a)
{
	return a < 0 ? -a : a;
}
int dist(int i, int j)
{
	return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}
int min(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	freopen("marathon.in", "r", stdin);
	freopen("marathon.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", x + i, y + i);
	for(int i = 1; i < n; ++i)
	{
		f[i][0] = f[i - 1][0] + dist(i, i - 1);
		if(i > 1)
			f[i][1] = min(f[i - 2][0] + dist(i, i - 2), f[i - 1][1] + dist(i, i - 1));
		else
			f[i][1] = 0x3f3f3f3f;
	}
	printf("%d\n", min(f[n - 1][0], f[n - 1][1]));
	fclose(stdin);
	fclose(stdout);
	return 0;
}
