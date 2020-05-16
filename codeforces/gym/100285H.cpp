#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int n, a, b, c1, c2, x[maxn], y[maxn], e[maxn][maxn], match[maxn], ans;
bool vis[maxn];
bool path(int u)
{
	for(int i = 1; i <= e[u][0]; ++i)
	{
		int &v = e[u][i];
		if(vis[v])
			continue;
		vis[v] = 1;
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
	int n;
	scanf("%d%d%d", &a, &b, &n);
	while(n--)
	{
		int ti, di;
		scanf("%d%d", &ti, &di);
		if(di == 0)
			x[c1++] = ti;
		else
			y[c2++] = ti;
	}
	sort(x, x + c1);
	sort(y, y + c2);
	if(c1 != c2)
	{
		puts("Liar");
		return 0;
	}
	for(int i = 0; i < c1; ++i)
		for(int j = 0; j < c2; ++j)
			if(x[i] <= y[j] && (y[j] <= x[i] + b || y[j] >= x[i] + a))
				e[i][++e[i][0]] = j;
	memset(match, -1, sizeof match);
	for(int i = 0; i < c1; ++i)
	{
		memset(vis, 0, sizeof vis);
		if(!path(i))
		{
			puts("Liar");
			return 0;
		}
	}
	puts("No reason");
	for(int i = 0; i < c2; ++i)
		printf("%d %d\n", x[match[i]], y[i]);
	return 0;
}
