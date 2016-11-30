#include <map>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 23333333, mod = 1000000000, maxd = 8;
int tot, prime[maxn >> 3], d[maxn], s[maxn];
int n, p, sz, ans;
LL m;
std::map<LL, int> Hash;
std::map<std::pair<int, LL>, int> Hash2;
int F(LL val)
{
	if(val < maxn)
		return s[(int)val];
	if(Hash.count(val))
		return Hash[val];
	int ret = val & 1 ? val % mod * ((val + 1 >> 1) % mod) % mod : (val >> 1) % mod * ((val + 1) % mod) % mod;
	for(LL i = 2, j, k; i <= val; i = j)
	{
		k = val / i;
		j = val / k + 1;
		ret = (ret - (j - i) % mod * F(k)) % mod;
	}
	if(ret < 0)
		ret += mod;
	return Hash[val] = ret;
}
int G(int n, LL m)
{
	if(!m)
		return 0;
	if(m == 1)
	{
		int ret = F(n) - F(n - 1);
		return ret < 0 ? ret + mod : ret;
	}
	if(n == 1)
		return F(m);
	std::pair<int, LL> state = std::make_pair(n, m);
	if(Hash2.count(state))
		return Hash2[state];
	int ret = (G(n, m / d[n]) + (d[n] - 1LL) * G(n / d[n], m)) % mod;
	return Hash2[state] = ret;
}
int main()
{
	s[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			prime[tot++] = d[i] = i;
			s[i] = i - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; prime[j] <= k; ++j)
		{
			int o = i * prime[j];
			d[o] = prime[j];
			if(d[i] == prime[j])
			{
				s[o] = s[i] * prime[j];
				break;
			}
			else
				s[o] = s[i] * (prime[j] - 1);
		}
		if((s[i] += s[i - 1]) >= mod)
			s[i] -= mod;
	}
	while(scanf("%d%lld", &n, &m) == 2)
	{
		std::map<LL, int>().swap(Hash);
		std::map<std::pair<int, LL>, int>().swap(Hash2);
		printf("%d\n", G(n, m));
	}
	return 0;
}

