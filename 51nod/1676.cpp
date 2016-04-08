#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 200, maxm = 4000;
const int mod = 985661441, seed = 2333;
int t, n, m, tot[2], p[2][maxn], h[2][maxn], sz, tmp[maxn], hh[maxn];
struct Edge
{
	int nxt, v;
} e[2][maxm << 1];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int o = 0; o < 2; ++o)
		{
			tot[o] = 0;
			memset(p[o], -1, n * sizeof(int));
			for(int i = 0, u, v; i < m; ++i)
			{
				scanf("%d%d", &u, &v);
				--u, --v;
				e[o][tot[o]] = (Edge){p[o][u], v};
				p[o][u] = tot[o]++;
				e[o][tot[o]] = (Edge){p[o][v], u};
				p[o][v] = tot[o]++;
			}
			for(int i = 0; i < n; ++i)
				h[o][i] = 1;
			for(int t = 0; t < n; ++t)
			{
				for(int i = 0; i < n; ++i)
				{
					sz = 0;
					tmp[sz++] = h[o][i];
					for(int it = p[o][i]; it != -1; it = e[o][it].nxt)
						tmp[sz++] = h[o][e[o][it].v];
					sort(tmp, tmp + sz);
					hh[i] = 0;
					for(int j = 0; j < sz; ++j)
						hh[i] = ((LL)hh[i] * seed + tmp[j]) % mod;
				}
				memcpy(h[o], hh, n * sizeof(int));
			}
			sort(h[o], h[o] + n);
		}
		bool flag = 1;
		for(int i = 0; i < n && flag; ++i)
			flag &= h[0][i] == h[1][i];
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
