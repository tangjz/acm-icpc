#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 301, INF = 0x3f3f3f3f;
int n, m, nL, nR, L[maxn], R[maxn], f[maxn * maxn >> 1], ans;
inline int idx(int i, int j, int o)
{
	return ((i * (nR + 1)) + j) * 2 + o;
}
inline void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		if(x < 0)
			L[++nL] = -x;
		else
			R[++nR] = x;
	}
	sort(L + 1, L + nL + 1);
	sort(R + 1, R + nR + 1);
	for(int d = 1; d <= n; ++d)
	{
		for(int i = 0; i <= nL; ++i)
			for(int j = 0, k = min(nR, d - i); j <= k; ++j)
			{
				if(!i && !j)
					continue;
				f[idx(i, j, 0)] = f[idx(i, j, 1)] = -INF;
				if(i)
				{
					upd(f[idx(i, j, 0)], f[idx(i - 1, j, 0)] - (L[i] - L[i - 1]) * (d - i - j + 1) + m);
					upd(f[idx(i, j, 0)], f[idx(i - 1, j, 1)] - (L[i] + R[j]) * (d - i - j + 1) + m);
				}
				if(j)
				{
					upd(f[idx(i, j, 1)], f[idx(i, j - 1, 0)] - (L[i] + R[j]) * (d - i - j + 1) + m);
					upd(f[idx(i, j, 1)], f[idx(i, j - 1, 1)] - (R[j] - R[j - 1]) * (d - i - j + 1) + m);
				}
			}
		for(int i = max(d - nR, 0), j = min(d, nL); i <= j; ++i)
		{
			upd(ans, f[idx(i, d - i, 0)]);
			upd(ans, f[idx(i, d - i, 1)]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
