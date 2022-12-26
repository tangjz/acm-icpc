#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, s, t, a, b, city[401][2], x[4], y[4];
double g[401][401], ans;
bool check(const int i, const int j, const int k) { return (x[j] - x[i]) * (x[j] - x[k]) + (y[j] - y[i]) * (y[j] - y[k]) == 0; }
int main()
{
	int i, j, u, v, tt;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d%d%d%d", &s, &t, &a, &b);
		for(i = 1; i <= s; ++i)
		{
			scanf("%d%d%d%d%d%d%d", &x[0], &y[0], &x[1], &y[1], &x[2], &y[2], &tt);
			if(check(0, 1, 2)) x[3] = x[0] - x[1] + x[2], y[3] = y[0] - y[1] + y[2];
			else if(check(1, 0, 2)) x[3] = x[1] - x[0] + x[2], y[3] = y[1] - y[0] + y[2];
			else if(check(0, 2, 1)) x[3] = x[0] - x[2] + x[1], y[3] = y[0] - y[2] + y[1];
			city[i * 4 - 3][0] = x[0], city[i * 4 - 3][1] = y[0];
			city[i * 4 - 2][0] = x[1], city[i * 4 - 2][1] = y[1];
			city[i * 4 - 1][0] = x[2], city[i * 4 - 1][1] = y[2];
			city[i * 4][0] = x[3], city[i * 4][1] = y[3];
			for(u = i * 4 - 3; u <= i * 4; ++u)
				for(v = u + 1; v <= i * 4; ++v)
					g[u][v] = g[v][u] = sqrt((city[u][0] - city[v][0]) * (city[u][0] - city[v][0]) + (city[u][1] - city[v][1]) * (city[u][1] - city[v][1])) * tt;
		}
		for(i = 1; i <= s; ++i)
			for(j = i + 1; j <= s; ++j)
				for(u = i * 4 - 3; u <= i * 4; ++u)
					for(v = j * 4 - 3;v <= j * 4; ++v)
						g[u][v] = g[v][u] = sqrt((city[u][0] - city[v][0]) * (city[u][0] - city[v][0]) + (city[u][1] - city[v][1]) * (city[u][1] - city[v][1])) * t;
		for(i = 1; i <= s * 4; ++i)
			for(u = 1; u <= s * 4; ++u)
				for(v = 1; v <= s * 4; ++v)
					if(g[u][v] > g[u][i] + g[i][v]) g[u][v] = g[u][i] + g[i][v];
		ans = 2147483647.0;
		for(u = a * 4 - 3; u <= a * 4; ++u)
			for(v = b * 4 - 3; v <= b * 4; ++v)
				if(ans > g[u][v]) ans = g[u][v];
		printf("%.1lf\n", ans);
	}
	return 0;
}
