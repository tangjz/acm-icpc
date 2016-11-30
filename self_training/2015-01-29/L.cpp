#include <map>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int mod = 2008;
map<int, int> Hash;
int pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = ret * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ret;
}
int dfs(int n)
{
	if(Hash.find(n) != Hash.end())
		return Hash[n];
	int ret = 0;
	for(int i = 2, j = (int)sqrt(n); i <= j; ++i)
		if(n % i == 0)
		{
			ret += dfs(i);
			if(ret >= mod)
				ret -= mod;
			if(n / i != i)
			{
				ret += dfs(n / i);
				if(ret >= mod)
					ret -= mod;
			}
		}
	ret = (pow(2, n) - ret - 2) % mod;
	if(ret < 0)
		ret += mod;
	return Hash[n] = ret;
}
int main()
{
	int n;
	Hash[1] = 2;
	while(scanf("%d", &n) != EOF)
		printf("%d\n", dfs(n));
	return 0;
}

