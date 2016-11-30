#include <map>
#include <stdio.h>
const int mod = 1000000007;
typedef long long LL;
std::map<int, int> Hash;
int n, ch;
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int dfs(int n)
{
	if(Hash.count(n))
		return Hash[n];
	int ret = mod_pow(ch, n) - ch;
	if(ret < 0)
		ret += mod;
	for(int i = 2; i * i <= n; ++i)
		if(n % i == 0)
		{
			if((ret -= dfs(i)) < 0)
				ret += mod;
			if(i * i < n && (ret -= dfs(n / i)) < 0)
				ret += mod;
		}
	return Hash[n] = ret;
}
int main()
{
	scanf("%d%d", &n, &ch);
	int ans = (ch + (LL)n * dfs(n)) % mod;
	for(int i = 2; i * i <= n; ++i)
		if(n % i == 0)
		{
			ans = (ans + (LL)i * dfs(i)) % mod;
			if(i * i < n)
				ans = (ans + (LL)(n / i) * dfs(n / i)) % mod;
		}
	printf("%d\n", ans);
	return 0;
}
