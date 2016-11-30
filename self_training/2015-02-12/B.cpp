#include <ctime>
#include <cstdio>
#include <cstdlib>
const int maxn = 32, maxc = 901, maxs = 1000001, dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int n, m, s[maxn][maxn], t[maxn][maxn], cnt[maxc], ans, out[maxs][2];
bool vis[maxn][maxn], trans;
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int abs(int x)
{
	return x < 0 ? -x : x;
}
void move(int x, int y)//move (x2, y2) to (x, y) start at (x1, y1)
{
	int x1 = out[ans - 1][0], y1 = out[ans - 1][1], x2 = 0, y2, xx, yy, xxx, yyy, dist, tmp;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(!vis[i][j] && s[i][j] == t[x][y] && !(i == x1 && j == y1))
			{
				x2 = i;
				y2 = j;
			}
	for(dist = abs(x2 - x1) + abs(y2 - y1); dist > 1; dist = tmp)
	{
		for(int i = 0; i < 8; ++i)
		{
			xx = x1 + dx[i];
			yy = y1 + dy[i];
			tmp = abs(xx - x2) + abs(yy - y2);
			if(!vis[xx][yy] && tmp < dist && !(xx == x2 && yy == y2))
				break;
		}
		swap(s[xx][yy], s[x1][y1]);
		out[ans][0] = x1 = xx;
		out[ans++][1] = y1 = yy;
	}
	for(dist = abs(x2 - x) + abs(y2 - y); !(x2 == x && y2 == y); dist = tmp)
	{
		while(1)
		{
			int i = rand() & 7;//be careful! infinite loop!
			xx = x1 + dx[i];
			yy = y1 + dy[i];
			if(xx == x2 && yy == y2)
			{
				xxx = x1;
				yyy = y1;
			}
			else
			{
				xxx = x2;
				yyy = y2;
			}
			tmp = abs(xxx - x) + abs(yyy - y);
			if(!vis[xx][yy] && abs(xx - xxx) <= 1 && abs(yy - yyy) <= 1 && tmp <= dist)
				break;
		}
		swap(s[xx][yy], s[x1][y1]);
		out[ans][0] = x1 = xx;
		out[ans++][1] = y1 = yy;
		x2 = xxx;
		y2 = yyy;
	}
	vis[x][y] = 1;
}
int main()
{
	srand(time(0));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			scanf("%d", &s[i][j]);
			++cnt[s[i][j]];
		}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			scanf("%d", &t[i][j]);
			--cnt[t[i][j]];
		}
	for(int i = 0; i < maxc; ++i)
		if(cnt[i])
		{
			puts("-1");
			return 0;
		}
	if(n > m)
	{
		trans = 1;
		for(int i = 1; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j)
			{
				swap(s[i][j], s[j][i]);
				swap(t[i][j], t[j][i]);
			}
		swap(n, m);
	}
	if(n == 1)
	{
		int l, r;
		bool flag;
		for(l = 1; s[1][l] == t[1][l]; ++l);
		for(r = m; s[1][r] == t[1][r]; --r);
		flag = s[1][l] == t[1][r];
		for(int i = l + 1; i <= r; ++i)
			flag &= s[1][i] == t[1][i - 1];
		if(flag)
		{
			printf("%d\n", r - l);
			for(int i = l; i <= r; ++i)
			{
				int x = 1, y = i;
				if(trans)
					swap(x, y);
				printf("%d %d\n", x, y);
			}
			return 0;
		}
		flag = s[1][r] == t[1][l];
		for(int i = l; i < r; ++i)
			flag &= s[1][i] == t[1][i + 1];
		if(flag)
		{
			printf("%d\n", r - l);
			for(int i = r; i >= l; --i)
			{
				int x = 1, y = i;
				if(trans)
					swap(x, y);
				printf("%d %d\n", x, y);
			}
			return 0;
		}
		puts("-1");
		return 0;
	}
	for(int i = 0; i <= n + 1; ++i)
		vis[i][0] = vis[i][m + 1] = 1;
	for(int i = 1; i <= m; ++i)
		vis[0][i] = vis[n + 1][i] = 1;
	for(int i = 1; i <= n && !ans; ++i)
		for(int j = 1; j <= m && !ans; ++j)
			if(s[i][j] == t[n][m])
			{
				out[ans][0] = i;
				out[ans++][1] = j;
			}
	for(int i = 1; i < n - 1; ++i)
		for(int j = 1; j <= m; ++j)
			move(i, j);
	for(int i = 1; i < m; ++i)
	{
		move(n - 1, i);
		move(n, i);
	}
	move(n - 1, m);
	printf("%d\n", ans - 1);
	for(int i = 0; i < ans; ++i)
	{
		if(trans)
			swap(out[i][0], out[i][1]);
		printf("%d %d\n", out[i][0], out[i][1]);
	}
	return 0;
}
