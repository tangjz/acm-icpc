#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 500001;
int n, m, mod, tot, p[maxn], pw[maxn], a[maxn], b[maxn];
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
void NTT(int x[maxn], int flag)
{
	// go deeper
	static int y[maxn] = {};
	int *cur = x, *nxt = y;
	for(int i = tot - 1, delta = n / p[i]; i > 0; --i, delta /= p[i], swap(cur, nxt))
		for(int j = 0, *np = nxt; j < n; j += delta * p[i])
			for(int k = 0; k < p[i]; ++k)
				for(int l = 0, *cp = cur + j + k; l < delta; ++l, ++np, cp += p[i])
					*np = *cp;
	// recursion
	for(int i = 0, clen = 1, nlen = p[i]; i < tot; ++i, clen = nlen, nlen *= p[i], swap(cur, nxt))
		for(int j = 0, k = 0, ww = 1, delta = 0; j < n; ++j, k = k + 1 < clen ? k + 1 : 0, ww = (LL)ww * pw[i] % mod, delta = delta + nlen > j ? delta : delta + nlen)
		{
			nxt[j] = 0;
			for(int t = 0, www = 1; t < nlen; t += clen, www = (LL)www * ww % mod)
				nxt[j] = (nxt[j] + (LL)www * cur[delta + t + k]) % mod;
		}
	if(flag == -1)
	{
		reverse(cur + 1, cur + n);
		for(int i = 0; i < n; ++i)
			cur[i] = (LL)cur[i] * n % mod; // n * n mod (n + 1) = 1
	}
	if(cur != x)
		memcpy(x, cur, n * sizeof(int));
}
int main()
{
	int tmp;
	scanf("%d%d", &n, &m);
	mod = n + 1;
	tmp = n;
	m = (m - 1) % n + 1;
	for(int i = 2; i * i <= tmp; ++i)
		for( ; tmp % i == 0; tmp /= i, p[tot++] = i);
	if(tmp > 1)
		p[tot++] = tmp;
	for(int ori = 2; ; ++ori)
	{
		bool flag = 1;
		for(int i = 0; i < tot && flag; ++i)
			if(!i || p[i - 1] != p[i])
				flag &= mod_pow(ori, n / p[i]) != 1;
		if(flag)
		{
			pw[tot - 1] = ori;
			for(int i = tot - 2; i >= 0; --i)
				pw[i] = mod_pow(pw[i + 1], p[i + 1]);
			break;
		}
	}
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	NTT(a, 1);
	for(int i = 0; i < n; ++i)
		scanf("%d", b + i);
	NTT(b, 1);
	for(int i = 0; i < n; ++i)
		a[i] = (LL)a[i] * mod_pow(b[i], m) % mod;
	NTT(a, -1);
	for(int i = 0; i < n; ++i)
		printf("%d\n", a[i]);
	return 0;
}
