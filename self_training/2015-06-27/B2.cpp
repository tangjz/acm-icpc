#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1500001, maxm = 1500001, maxd = 21, mod = 1000000007;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, a[maxn], tot, prime[maxm], fact[maxm];
LL f[2][maxd][maxd], ans;
vector<pair<int, int> > e[maxm];
void upd(LL &x, LL y)
{
	if((x += y) >= mod)
		x -= mod;
}
int main()
{
	scanf("%d%d", &n, &m);
	//for(int i = 1; i <= n; ++i)
	//	scanf("%d", a + i);
	a[1] = (1426 - 1) % m + 1;
	for(int i = 2; i <= n; ++i)
		a[i] = (1394LL * a[i - 1] + 2015) % m + 1;
	for(int i = 2; i <= m; ++i)
	{
		if(!fact[i])
			fact[i] = prime[tot++] = i;
		for(int j = 0; j < tot && (LL)i * prime[j] <= m; ++j)
		{
			fact[i * prime[j]] = prime[j];
			if(i % prime[j] == 0)
				break;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
	//	printf("%d%c", a[i], " \n"[i == n]);
		for(int tmp = a[i]; tmp > 1; )
		{
			int cnt = 0, pr = fact[tmp];
			for( ; fact[tmp] == pr; tmp /= pr, ++cnt);
			e[pr].push_back(make_pair(i, cnt));
		}
	}
	ans = 1;
	for(int i = 1; i <= m; ++i)
	{
		if(!e[i].size())
			continue;
		int pid = 0, psz = 0, cur = 0, pre = 1;
		f[cur][0][0] = 1;
		for(vector<pair<int, int> >::iterator it = e[i].begin(); it != e[i].end(); ++it)
		{
			int cid = it -> first, csz = it -> second;
			if(pid + 1 < cid)
			{
				LL tmp = 0;
				for(int k = 0; k <= psz; ++k)
					upd(tmp, f[cur][0][k]);
				f[cur][0][0] = tmp;
				psz = 0;
			}
			cur ^= 1;
			pre ^= 1;
			for(int j = 0; j <= csz; ++j)
				memset(f[cur][j], 0, (csz + 1) * sizeof(LL));
			for(int j = 0; j <= psz; ++j)
				for(int k = 0; k <= psz; ++k)
					for(int l = j; l <= csz; ++l)
						upd(f[cur][l - j][csz - l], f[pre][j][k]);
			pid = cid;
			psz = csz;
		}
		LL tmp = 0;
		for(int k = 0; k <= psz; ++k)
			upd(tmp, f[cur][0][k]);
		ans = (LL)ans * tmp % mod;
	}
	printf("%I64d\n", ans);
	return 0;
}
