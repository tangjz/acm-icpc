#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 302, INF = 0x3f3f3f3f;
int t, n, qn, que[maxn], suf[maxn], p[maxn][maxn], f[maxn][maxn];
struct Monster
{
	int L, R, D;
	bool operator < (const Monster &x) const
	{
		return D > x.D;
	}
} a[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(p, -1, sizeof p);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", &a[i].L, &a[i].R, &a[i].D);
			que[i] = a[i].R;
		}
		sort(a, a + n);
		sort(que, que + n);
		qn = unique(que, que + n) - que;
		for(int i = 0; i <= qn; ++i)
			suf[i] = qn + 1;
		for(int i = 0; i < n; ++i)
		{
			a[i].L = lower_bound(que, que + qn, a[i].L) - que + 1;
			a[i].R = lower_bound(que, que + qn, a[i].R) - que + 1;
			for(int l = 0; l < a[i].L; ++l)
			{
				if(a[i].R >= suf[l])
					continue;
				for(int r = a[i].R + 1; r <= suf[l]; ++r)
					p[l][r] = i;
				suf[l] = a[i].R;
			}
		}
		++qn;
		for(int l = 0; l <= qn; ++l)
			for(int i = 0; i <= qn - l; ++i)
			{
				int j = i + l;
				int &pos = p[i][j];
				if(pos == -1)
				{
					f[i][j] = 0;
					continue;
				}
				f[i][j] = INF;
				for(int k = a[pos].L; k <= a[pos].R; ++k)
					if(f[i][j] > f[i][k] + f[k][j] + a[pos].D)
						f[i][j] = f[i][k] + f[k][j] + a[pos].D;
			}
		printf("%d\n", f[0][qn]);
	}
	return 0;
}
