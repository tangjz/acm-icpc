#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 100000, mod = 1000000007;
int tot, prime[maxn], t, n, cnt, seq[maxn][2], ans;
bool vis[maxn];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
void dfs(int dep, int sum, int phi)
{
	if(dep == cnt)
	{
		inc(ans, ((LL)phi * sum >> 1) % mod);
		return;
	}
	dfs(dep + 1, sum, phi);
	for(int i = 0; i < seq[dep][1]; ++i)
	{
		sum *= seq[dep][0];
		phi *= seq[dep][0] - (!i);
		dfs(dep + 1, sum, phi);
	}
}
int main()
{
	scanf("%d", &t);
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && (LL)i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	while(t--)
	{
		scanf("%d", &n);
		int tmp = n;
		ans = cnt = 0;
		for(int i = 0; i < tot && (LL)prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
			{
				seq[cnt][0] = prime[i];
				seq[cnt][1] = 0;
				for( ; tmp % prime[i] == 0; tmp /= prime[i])
					++seq[cnt][1];
				++cnt;
			}
		if(tmp > 1)
		{
			seq[cnt][0] = tmp;
			seq[cnt++][1] = 1;
		}
		dfs(0, 1, 1);
		inc(ans, 1);
		ans = (LL)ans * n % mod;
		printf("%d\n", ans);
	}
	return 0;
}
