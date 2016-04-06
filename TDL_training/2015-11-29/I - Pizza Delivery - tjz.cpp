#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 101, INF = 0x3f3f3f3f;
int t, n, p[maxn], v[maxn], f[maxn][maxn][maxn][2], ans;
inline void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int F(int i, int j, int d, int o)
{
	if(!d)
		return 0;
	if(f[i][j][d][o] != -1)
		return f[i][j][d][o];
	int ret = 0;
	if(o)
	{
		for(int k = 0; k < i; ++k)
			upd(ret, F(k, j, d - 1, 0) - d * (p[j] - p[k]) + v[k]);
		for(int k = j + 1; k < n; ++k)
			upd(ret, F(i, k, d - 1, 1) - d * (p[k] - p[j]) + v[k]);
	}
	else
	{
		for(int k = 0; k < i; ++k)
			upd(ret, F(k, j, d - 1, 0) - d * (p[i] - p[k]) + v[k]);
		for(int k = j + 1; k < n; ++k)
			upd(ret, F(i, k, d - 1, 1) - d * (p[k] - p[i]) + v[k]);
	}
	return f[i][j][d][o] = ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(f, -1, sizeof f);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", p + i);
		for(int i = 0; i < n; ++i)
			scanf("%d", v + i);
		ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < n; ++j)
				upd(ans, F(j, j, i - 1, 0) - i * abs(p[j]) + v[j]);
		printf("%d\n", ans);
	}
	return 0;
}
