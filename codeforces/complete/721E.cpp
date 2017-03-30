#include <cstdio>
#include <algorithm>
const int maxn = 100001;
int len, n, m, dt, pL[maxn], pR[maxn], f[maxn], p[maxn];
int main()
{
	scanf("%d%d%d%d", &len, &n, &m, &dt);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", pL + i, pR + i);
	p[0] = pL[1] - dt;
	for(int i = 1, j = 0; i <= n; ++i)
	{
		// skip
		f[i] = f[i - 1];
		p[i] = p[i - 1];
		// do sth
		for( ; j < i && p[j] + dt <= pR[i]; ++j)
		{
			int sta = std::max(p[j] + dt, pL[i]), cnt = (pR[i] - sta) / m;
			int cf = f[j] + cnt, cp = sta + cnt * m;
			if(f[i] < cf)
			{
				f[i] = cf;
				p[i] = cp;
			}
			else if(f[i] == cf && cp < p[i])
				p[i] = cp;
		}
		--j;
	}
	printf("%d\n", f[n]);
	return 0;
}
