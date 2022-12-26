#include <stdio.h>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int maxn = 37, maxd = 18, maxs = 1 << maxd;
unordered_map<LL, LL> pre, cur;
int n, a[maxn], bits[maxs + 1], lbt[maxs + 1];
int popcount(LL x)
{
	return bits[x >> maxd] + bits[x & (maxs - 1)];
}
int lowbit(LL x, int pos)
{
	LL y = x >> pos;
	if(y & (maxs - 1))
		return pos + lbt[y & (maxs - 1)];
	if(y >> maxd)
		return pos + maxd + lbt[y >> maxd];
	return -1;
}
int main()
{
	for(int i = 1; i < maxs; ++i)
	{
		bits[i] = bits[i >> 1] + (i & 1);
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
	}
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		--a[i];
	}
	cur[0LL] = 1;
	for(int i = 1; i <= n; ++i)
	{
		cur.swap(pre);
		unordered_map<LL, LL>().swap(cur);
		int L = -1, M = a[i], R = n;
		for(int j = i + 1; j <= n; ++j)
			if(a[j] < M)
			{
				if(L < a[j])
					L = a[j];
			}
			else // M < a[j]
			{
				if(a[j] < R)
					R = a[j];
			}
		for(auto &it : pre)
		{
			LL u = it.first, ways = it.second, v = u;
			// merge [L+1, M-1] [M+1, R-1] -> [L+1, R-1]
			LL mask = (v >> (L + 1)) & ((1LL << (R - L - 1)) - 1); // get [L+1, R-1]
			v ^= (mask ^ ((1LL << popcount(mask)) - 1)) << (L + 1); // sort [L+1, R-1]
			int fir = lowbit(u, M + 1), las;
			// not select
			cur[v] += fir == M + 1 ? ways << 1 : ways;
			// select
			if(fir != M + 1)
			{
				if(fir != -1)
				{
					las = lowbit(v + (1LL << fir), fir) - 1;
					v ^= 1LL << las; // 1 -> 0
				}
				las = lowbit(v + (1LL << (L + 1)), L + 1);
				v ^= 1LL << las; // 0 -> 1
				cur[v] += ways;
			}
		}
	}
	for(int i = 0; i <= n; ++i)
		printf("%lld\n", cur.count((1LL << i) - 1) ? cur[(1LL << i) - 1] : 0);
	return 0;
}
