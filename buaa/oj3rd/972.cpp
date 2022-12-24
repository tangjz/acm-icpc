#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100002, maxd = 17;
map<LL, LL> cnt;
int t, n, m, Log[maxn];
LL st[maxn][maxd];
LL rmq(int L, int R)
{
	if(L > R)
		return 0;
	int d = Log[R - L + 1];
	return st[L][d] & st[R - (1 << d) + 1][d];
}
int main()
{
	for(int i = 2; i < maxn; ++i)
		Log[i] = Log[i >> 1] + 1;
	scanf("%d", &t);
	while(t--)
	{
		cnt.clear();
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%lld", st[i] + 0);
		st[n][0] = 0;
		for(int d = 1; d <= Log[n + 1]; ++d)
			for(int i = 0; i + (1 << d - 1) <= n; ++i)
				st[i][d] = st[i][d - 1] & st[i + (1 << d - 1)][d - 1];
		for(int i = 0; i < n; ++i)
			for(int j = i; j < n; ++j)
			{
				int L = j, R = n, M;
				LL v = rmq(i, j);
				while(L < R)
				{
					M = L + R + 1 >> 1;
					if(rmq(i, M) < v)
						R = M - 1;
					else
						L = M;
				}
				cnt[v] += L - j + (L < n);
				j = L;
			}
		for(int i = 0; i < m; ++i)
		{
			LL x;
			scanf("%lld", &x);
			printf("%lld\n", cnt.count(x) ? cnt[x] : 0);
		}
	}
	return 0;
}
