#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 210;
struct Box
{
	int x, y;
	bool operator < (const Box &t) const
	{
		return x < t.x || x == t.x && y < t.y;
	}
	bool operator == (const Box &t) const
	{
		return x == t.x && y == t.y;
	}
} a[maxn];
int n, g[maxn][maxn], lx[maxn], ly[maxn], match[maxn], ans;
bool sx[maxn], sy[maxn];
bool path(int u)
{
	sx[u] = 1;
	for(int v = 0; v < n; ++v)
	{
		if(sy[v] || lx[u] + ly[v] != g[u][v])
			continue;
		sy[v] = 1;
		if(match[v] == -1 || path(match[v]))
		{
			match[v] = u;
			return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &a[i].x, &a[i].y);
	sort(a, a + n);
	n = unique(a, a + n) - a;
	for(int i = 0; i < n; ++i)
	{
		ans += a[i].x * a[i].y;
		for(int j = i + 1; j < n; ++j)
			if(a[i].x <= a[j].x && a[i].y <= a[j].y)
				g[i][j] = a[i].x * a[i].y;
		lx[i] = a[i].x * a[i].y;
	}
	memset(match, -1, sizeof match);
	for(int i = 0; i < n; ++i)
		while(1)
		{
			memset(sx, 0, sizeof sx);
			memset(sy, 0, sizeof sy);
			if(path(i))
				break;
			int dx = 0x3f3f3f3f;
			for(int j = 0; j < n; ++j)
			{
				if(!sx[j])
					continue;
				for(int k = 0; k < n; ++k)
					if(!sy[k] && dx > lx[j] + ly[k] - g[j][k])
						dx = lx[j] + ly[k] - g[j][k];
			}
			for(int j = 0; j < n; ++j)
			{
				if(sx[j])
					lx[j] -= dx;
				if(sy[j])
					ly[j] += dx;
			}
		}
	for(int i = 0; i < n; ++i)
		if(match[i] != -1)
			ans -= g[match[i]][i];
	printf("%d\n", ans);
	return 0;
}
