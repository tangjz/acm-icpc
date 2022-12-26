/*
 * 二维树状数组解决矩形修改、求和
 */
#include <cstdio>
const int maxn = 2049;
int n, m, bit[maxn][maxn][4];
inline void swap(int &x, int &y) { int t = x; x = y; y = t; }
void add(int x, int y, int val)
{
	for(int i = x; i <= n; i += i & -i)
		for(int j = y; j <= m; j += j & -j)
		{
			bit[i][j][0] += val;
			bit[i][j][1] += val * x;
			bit[i][j][2] += val * y;
			bit[i][j][3] += val * x * y;
		}
}
int sum(int x, int y)
{
	int cnt = 0;
	for(int i = x; i; i -= i & -i)
		for(int j = y; j; j -= j & -j)
			cnt += bit[i][j][0] * (x + 1) * (y + 1) - bit[i][j][1] * (y + 1) - bit[i][j][2] * (x + 1) + bit[i][j][3];
	return cnt;
}
int main()
{
	char t;
	int x1, x2, y1, y2, val;
	scanf("%*c%d%d", &n, &m);
	while((t = getchar()) != EOF)
	{
		if(t == '\r' || t == '\n') continue;
		if(t == 'L')
		{
			scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &val);
			if(x1 > x2) swap(x1, x2);
			if(y1 > y2) swap(y1, y2);
			add(x1, y1, val);
			add(x2 + 1, y1, -val);
			add(x1, y2 + 1, -val);
			add(x2 + 1, y2 + 1, val);
		}
		else
		{
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if(x1 > x2) swap(x1, x2);
			if(y1 > y2) swap(y1, y2);
			printf("%d\n", sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1));
		}
	}
	return 0;
}
