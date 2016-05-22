#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 401, maxm = 801;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, fb[maxm], fc[maxm];
struct Node
{
	int a, b, c;
	LL v;
} p[maxn];
LL f[maxm], ans;
pair<int, int> calc(int kx, int ky)
{
	memset(f, 0x3f, (m + 1) * sizeof(LL));
	f[0] = fb[0] = fc[0] = 0;
	for(int i = 1; i <= n; ++i)
	{
		p[i].v = (LL)kx * p[i].b + (LL)ky * p[i].c;
		for(int j = m - 1; j >= 0; --j)
		{
			if(f[j] == INF)
				continue;
			int k = min(j + p[i].a, m);
			if(f[k] > f[j] + p[i].v)
			{
				f[k] = f[j] + p[i].v;
				fb[k] = fb[j] + p[i].b;
				fc[k] = fc[j] + p[i].c;
			}
		}
	}
	ans = min(ans, (LL)fb[m] * fc[m]);
	return make_pair(fb[m], fc[m]);
}
void solve(pair<int, int> px, pair<int, int> py)
{
	if(px == py)
		return;
	pair<int, int> pp = calc(px.second - py.second, py.first - px.first);
	if(px == pp || py == pp)
		return;
	solve(px, pp);
	solve(pp, py);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		ans = INF;
		for(int i = 1; i <= n; ++i)
			scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
		solve(calc(1, 0), calc(0, 1));
		printf("%I64d\n", ans);
	}
	return 0;
}
