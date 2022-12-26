#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, s[maxn], tot, p[maxn], bit[maxn], ans;
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
}
void add(int x)
{
	for( ; x < tot; x += ~x & (x + 1))
		bit[x] ^= 1;
}
int sum(int x)
{
	int ret = 0;
	for( ; x >= 0; x -= ~x & (x + 1))
		ret ^= bit[x];
	return ret;
}
int idx(long long val)
{
	int L = -1, R = tot - 1;
	while(L < R)
	{
		int M = (L + R + 1) >> 1;
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
		scan(s[i]);
		s[i] += s[i - 1];
	}
	for(int k = 0; (1 << k) <= s[n]; ++k)
	{
		int tmp = 0;
		for(int i = 0; i <= n; ++i)
			p[i] = s[i] & ((1 << (k + 1)) - 1);
		sort(p, p + n + 1);
		tot = unique(p, p + n + 1) - p;
		memset(bit, 0, tot * sizeof(int));
		for(int i = 0; i <= n; ++i)
		{
			int now = s[i] & ((1 << (k + 1)) - 1);
			add(idx(now));
			tmp ^= sum(idx(now - (1 << k))) ^ sum(idx(now + (1 << k))) ^ sum(idx(now));
		}
		ans |= tmp << k;
	}
	printf("%d\n", ans);
	return 0;
}
