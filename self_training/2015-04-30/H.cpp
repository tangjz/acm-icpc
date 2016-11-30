#include <cstdio>
#include <cstring>
const int maxn = 100010, mod = 1000000007;
int pow(int x, unsigned int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % mod;
		x = (long long)x * x % mod;
		k >>= 1;
	}
	return ret;
}
char str[maxn];
int tran(char *s)
{
	int ret = 0;
	for(int i = 0; s[i]; ++i)
		ret = ((long long)ret * 10 + s[i] - '0') % (mod - 1);
	--ret;
	if(ret < 0)
		ret += mod - 1;
	return ret;
}
int main()
{
	while(scanf("%s", str) == 1)
		printf("%d\n", pow(2, tran(str)));
	return 0;
}
