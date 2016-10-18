#include <cstdio>
const int maxn = 100002, mod = 1e9 + 7;
const char *code = "AGCT";
int n, cnt[maxn], pos, ans;
char str[maxn];
int pow(int x, int k)
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
int main()
{
	scanf("%d%s", &n, str);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < 4; ++j)
			if(str[i] == code[j])
				++cnt[j];
	for(int i = 1; i < 4; ++i)
		if(cnt[i] > cnt[pos])
			pos = i;
	for(int i = 0; i < 4; ++i)
		if(cnt[i] == cnt[pos])
			++ans;
	printf("%d\n", pow(ans, n));
	return 0;
}
