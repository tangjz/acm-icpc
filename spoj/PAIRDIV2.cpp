#include <stdio.h>
#include <unordered_map>
typedef long long LL;
const int maxp = 100000, maxc = 17, maxd = 103681, mod = 1000000000;
int tot, pr[maxp], d[maxp], cnt, p[maxc], e[maxc], ans;
LL n, a, b;
int HashCounter;
std::unordered_map<LL, int> Hash;
inline int getID(LL key)
{
	if(!Hash.count(key))
		Hash[key] = HashCounter++;
	return Hash[key];
}
int ptot, pri[maxc], f[maxc][maxd];
void dfs(int dep, LL val)
{
	if(dep == cnt)
	{
		int idx = getID(val);
		f[0][idx] = a / (n / val) % mod;
		for(int i = 1; i <= ptot; ++i)
			if((f[i][idx] = f[i - 1][idx] - f[i - 1][getID(val / pri[i - 1])]) < 0)
				f[i][idx] += mod;
		ans = (ans + (b / val % mod) * f[ptot][idx]) % mod;
		return;
	}
	dfs(dep + 1, val);
	pri[ptot++] = p[dep];
	for(int i = 1; i <= e[dep]; ++i)
		dfs(dep + 1, val *= p[dep]);
	--ptot;
}
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int t;
	scanf("%d", &t);
	while(t--)
	{
		HashCounter = 0;
		std::unordered_map<LL, int>().swap(Hash);
		scanf("%lld%lld%lld", &n, &a, &b);
		cnt = 0;
		LL tmp = n;
		for(int i = 0; i < tot && (LL)pr[i] * pr[i] <= tmp; ++i)
			if(tmp % pr[i] == 0)
			{
				for(e[cnt] = 1, tmp /= pr[i]; tmp % pr[i] == 0; ++e[cnt], tmp /= pr[i]);
				p[cnt++] = pr[i];
			}
		if(tmp > 1)
		{
			e[cnt] = 1;
			p[cnt++] = tmp;
		}
		ans = 0;
		dfs(0, 1);
		printf("%d\n", ans);
	}
	return 0;
}
