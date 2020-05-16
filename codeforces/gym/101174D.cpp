#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef double DB;
const int maxn = 51, maxm = 11;
int n, m, q, c0, c1, c2, cnt[maxn];
DB lnF[maxn], f[maxm][maxm][maxm];
bool vis[maxm][maxm][maxm];
DB lnC(int n, int m) // assert(n >= m);
{
	return lnF[n] - lnF[m] - lnF[n - m];
}
DB F(int i, int j, int k)
{
	if(i > c0 || j > c1 || k > c2)
		return 0.0;
	if(k == c2 && (i == c0 || j == c1))
		return 0.0;
	if(vis[i][j][k])
		return f[i][j][k];
	vis[i][j][k] = 1;
	for(int u = 0, uLim = min(q, c0 - i); u <= uLim; ++u)
		for(int v = 0, vLim = min(q - u, c1 - j); v <= vLim; ++v)
			for(int w = 0, wLim = min(q - u - v, c2 - k); w <= wLim; ++w)
			{
				if(!(u + v + w))
					continue;
				DB coeff = n - (c0 - i) - (c1 - j) - (c2 - k) >= q - u - v - w ? exp(lnC(n - (c0 - i) - (c1 - j) - (c2 - k), q - u - v - w) + lnC(c0 - i, u) + lnC(c1 - j, v) + lnC(c2 - k, w) - lnC(n, q)) : 0.0;
				f[i][j][k] += F(i + u, j + v, k + w) * coeff;
				// printf("(%d, %d, %d) -> (%d, %d, %d) : %.10f\n", i, j, k, i + u, j + v, k + w, coeff);
				// printf("f %d %d %d : %.10f\n", i, j, k, f[i][j][k]);
			}
	DB coeff = n - (c0 - i) - (c1 - j) - (c2 - k) >= q ? exp(lnC(n - (c0 - i) - (c1 - j) - (c2 - k), q) - lnC(n, q)) : 0.0;
	// printf("(%d, %d, %d) -> (%d, %d, %d) : %.10f\n", i, j, k, i, j, k, coeff);
	f[i][j][k] = (1 + f[i][j][k]) / (1 - coeff);
	return f[i][j][k];
}
int main()
{
	scanf("%d%d%d", &n, &q, &m);
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < m; ++j)
		{
			int x;
			scanf("%d", &x);
			cnt[x] |= 1 << i;
		}
	for(int i = 1; i <= n; ++i)
	{
		c0 += cnt[i] == 1;
		c1 += cnt[i] == 2;
		c2 += cnt[i] == 3;
		lnF[i] = lnF[i - 1] + log(i);
	}
	printf("%.10f\n", F(0, 0, 0));
	return 0;
}
