#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001, maxm = 20001, maxsqn = 40;
int n, m, q, size, bcnt, a[maxn], first[maxsqn], c[maxsqn][maxsqn][maxm], tc[maxm];
int f[maxsqn][maxsqn][maxm], L, R, X, Y, ans;
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	size = 1360;
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; i += size)
	{
		first[++bcnt] = i;
		for(int j = first[bcnt]; j <= n && j < first[bcnt] + size; ++j)
			++c[bcnt][bcnt][a[j]];
	}
	for(int i = 1; i <= bcnt; ++i)
	{
		for(int k = 1; k <= m; ++k)
			f[i][i][k] = f[i][i][k - 1] + (LL)c[i][i][k] * c[i][i][k];
		for(int j = i + 1; j <= bcnt; ++j)
			for(int k = 1; k <= m; ++k)
			{
				c[i][j][k] = c[i][j - 1][k] + c[j][j][k];
				f[i][j][k] = f[i][j][k - 1] + (LL)c[i][j][k] * c[i][j][k];
			}
	}
	while(q--)
	{
		scanf("%d%d%d%d", &L, &R, &X, &Y);
		L ^= ans, R ^= ans, X ^= ans, Y ^= ans;
		int pL = upper_bound(first + 1, first + bcnt + 1, L) - first, pR = lower_bound(first + 1, first + bcnt + 1, R) - first - 2;
		if(pL <= pR)
		{
			ans = f[pL][pR][Y] - f[pL][pR][X - 1];
			for(int i = L; i < first[pL]; ++i)
				if(a[i] >= X && a[i] <= Y)
					ans += (c[pL][pR][a[i]]++) << 1 | 1;
			for(int i = first[pR] + size; i <= R; ++i)
				if(a[i] >= X && a[i] <= Y)
					ans += (c[pL][pR][a[i]]++) << 1 | 1;
			for(int i = L; i < first[pL]; ++i)
				if(a[i] >= X && a[i] <= Y)
					--c[pL][pR][a[i]];
			for(int i = first[pR] + size; i <= R; ++i)
				if(a[i] >= X && a[i] <= Y)
					--c[pL][pR][a[i]];
		}
		else
		{
			ans = 0;
			for(int i = L; i <= R; ++i)
				if(a[i] >= X && a[i] <= Y)
					ans += (tc[a[i]]++) << 1 | 1;
			for(int i = L; i <= R; ++i)
				if(a[i] >= X && a[i] <= Y)
					--tc[a[i]];
		}
		printf("%d\n", ans);
	}
	return 0;
}
