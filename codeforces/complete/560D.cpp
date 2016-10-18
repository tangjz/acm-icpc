#include <cstdio>
#include <cstring>
const int maxn = 200010, mod1 = 1000000007, mod2 = 1000000009;
typedef long long LL;
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
int slen, tlen, hs[maxn][2], ht[maxn][2];
char s[maxn], t[maxn];
bool hash_equiv(int s1, int s2, int t1, int t2)
{
	int hs1 = hs[s2][0] - (s1 ? (LL)hs[s1 - 1][0] * mod_pow(29, s2 - s1 + 1, mod1) % mod1 : 0);
	int hs2 = hs[s2][1] - (s1 ? (LL)hs[s1 - 1][1] * mod_pow(31, s2 - s1 + 1, mod2) % mod2 : 0);
	int ht1 = ht[t2][0] - (t1 ? (LL)ht[t1 - 1][0] * mod_pow(29, t2 - t1 + 1, mod1) % mod1 : 0);
	int ht2 = ht[t2][1] - (t1 ? (LL)ht[t1 - 1][1] * mod_pow(31, t2 - t1 + 1, mod2) % mod2 : 0);
	if(hs1 < 0)
		hs1 += mod1;
	if(hs2 < 0)
		hs2 += mod2;
	if(ht1 < 0)
		ht1 += mod1;
	if(ht2 < 0)
		ht2 += mod2;
	return hs1 == ht1 && hs2 == ht2;
}
bool equiv(int s1, int t1, int len)
{
	if(hash_equiv(s1, s1 + len - 1, t1, t1 + len - 1))
		return 1;
	if(len % 2 == 0)
		return equiv(s1, t1 + (len >> 1), len >> 1) && equiv(s1 + (len >> 1), t1, len >> 1)
			|| equiv(s1, t1, len >> 1) && equiv(s1 + (len >> 1), t1 + (len >> 1), len >> 1);
	return 0;
}
int main()
{
	scanf("%s%s", s, t);
	slen = strlen(s);
	tlen = strlen(t);
	hs[0][0] = hs[0][1] = s[0] - 'a';
	for(int i = 1; i < slen; ++i)
	{
		hs[i][0] = (hs[i - 1][0] * 29LL + s[i] - 'a') % mod1;
		hs[i][1] = (hs[i - 1][1] * 31LL + s[i] - 'a') % mod2;
	}
	ht[0][0] = ht[0][1] = t[0] - 'a';
	for(int i = 1; i < tlen; ++i)
	{
		ht[i][0] = (ht[i - 1][0] * 29LL + t[i] - 'a') % mod1;
		ht[i][1] = (ht[i - 1][1] * 31LL + t[i] - 'a') % mod2;
	}
	puts(equiv(0, 0, tlen) ? "YES" : "NO");
	return 0;
}
