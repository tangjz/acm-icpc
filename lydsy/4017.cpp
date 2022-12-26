#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100010, mod = 998244353;
int n, a[maxn], x[maxn], bit[maxn], ans1;
long long s[maxn], p[maxn], ans2;
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
}
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
void add(int x)
{
	for( ; x <= n; x += ~x & x + 1)
		bit[x] ^= 1;
}
int sum(int x)
{
	int ret = 0;
	for( ; x >= 0; x -= ~x & x + 1)
		ret ^= bit[x];
	return ret;
}
int idx(long long val)
{
	int L = -1, R = n;
	while(L < R)
	{
		int M = L + R + 1 >> 1;
		if(p[M] <= val)
			L = M;
		else
			R = M - 1;
	}
	return L;
}
int main()
{
	scan(n);
	for(int i = 1; i <= n; ++i)
	{
		scan(a[i]);
		x[i] = x[i - 1] ^ a[i];
		s[i] = s[i - 1] + a[i];
	}
	for(int k = 0, powk = 1; k < 30; ++k, inc(powk, powk))
	{
		int cnt[2] = {}, tmp = 0;
		for(int i = 0; i <= n; ++i)
		{
			inc(tmp, cnt[((x[i] >> k) & 1) ^ 1]);
			++cnt[(x[i] >> k) & 1];
		}
		inc(ans1, (long long)powk * tmp % mod);
	}
	for(int k = 0; 1LL << k < s[n]; ++k)
	{
		int tmp = 0;
		for(int i = 0; i <= n; ++i)
			p[i] = s[i] & ((1LL << k + 1) - 1);
		sort(p, p + n + 1);
		memset(bit, 0, sizeof bit);
		for(int i = 0; i <= n; ++i)
		{
			long long now = s[i] & ((1LL << k + 1) - 1);
			add(idx(now));
			tmp ^= sum(idx(now - (1LL << k))) ^ sum(idx(now + (1LL << k))) ^ sum(idx(now));
		}
		if(tmp)
			ans2 |= 1LL << k;
	}
	printf("%d %lld\n", ans1, ans2);
	return 0;
}
/*
4
7 4 10 2

80 16
*/
