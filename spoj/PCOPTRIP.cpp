#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<int, int> Edge;
const int maxn = 100001;
int t, n, mu[maxn], deg[maxn], ord[maxn], dis[maxn];
vector<Edge> e[maxn];
bool cmp(const int &x, const int &y)
{
	return deg[x] > deg[y];
}
int main()
{
	mu[1] = 1;
	for(int i = 1; i < maxn; ++i)
		for(int j = i + i; j < maxn; j += i)
			mu[j] -= mu[i];
	scanf("%d", &t);
	while(t--)
	{
		LL ans = 0;
		scanf("%d", &n);
		memset(deg + 1, 0, n * sizeof(int));
		for(int i = 1; i <= n; ++i)
		{
			vector<Edge>().swap(e[i]);
			ord[i] = i;
		}
		int tot = 0;
		for(int i = 1; i <= n; ++i) if(mu[i])
			for(int j = i, k = 1; j <= n; j += i, ++k)
				if(mu[k] && mu[j])
					for(int l = j, m = i, lim = n / i, o = m * i; l <= lim; l += k, ++m, o += i)
					{
						if(!mu[m] || !mu[l] || !mu[o])
							continue;
						e[j].push_back(make_pair(l, lim / l));
						if(j != l)
							e[l].push_back(make_pair(j, lim / l));
						++tot;
						++deg[j];
						if(j != l)
							++deg[l];
					}
		sort(ord + 1, ord + n + 1, cmp);
		for(int i = 1; i <= n; ++i)
		{
			vector<Edge> tmp;
			for(vector<Edge>::iterator it = e[i].begin(); it != e[i].end(); ++it)
				if(deg[i] >= deg[it -> first])
					tmp.push_back(*it);
			e[i].swap(tmp);
		}
		for(int i = 1; i <= n; ++i)
		{
			int u = ord[i];
			for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int v = it -> first, dv = it -> second;
				dis[v] = dv;
			}
			int sgn = mu[u], cnt = 3;
			for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int v = it -> first, dv = it -> second, tp = deg[u] > deg[v] ? cnt-- : 1;
				if(mu[v] < 0)
					sgn = -sgn;
				for(vector<Edge>::iterator it = e[v].begin(); it != e[v].end(); ++it)
				{
					int w = it -> first, dw = it -> second, way = (sgn < 0) == (mu[w] < 0) ? tp : -tp;
					if(deg[v] > deg[w])
						way *= cnt;
					ans += way * dis[w] * (LL)dv * dw;
				}
				if(mu[v] < 0)
					sgn = -sgn;
				if(deg[u] > deg[v])
					++cnt;
			}
			for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int v = it -> first;
				dis[v] = 0;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
