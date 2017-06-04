#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 5001;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, a[maxn], cur, pre = 1;
std::pair<int, int> b[maxn];
LL f[2][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d", &b[i].first, &b[i].second);
	std::sort(b + 1, b + m + 1);
	memset(f[cur] + 1, 0x3f, n * sizeof(LL));
	for(int i = 1; i <= m; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		// memcpy(f[cur], f[pre], (n + 1) * sizeof(LL));
		int len = 0;
		LL cost = 0;
		for(int j = 1; j <= n; ++j)
		{
			++len;
			cost += std::abs(a[j] - b[i].first);
			LL prev = f[pre][j - len] != INF && len <= b[i].second ? f[pre][j - len] + cost : INF;
			while(len > 0)
			{
				--len;
				cost -= std::abs(a[j - len] - b[i].first);
				LL curv = f[pre][j - len] != INF && len <= b[i].second ? f[pre][j - len] + cost : INF;
				if(prev < curv)
				{
					cost += std::abs(a[j - len] - b[i].first);
					++len;
					break;
				}
				prev = curv;
			}
			f[cur][j] = prev;
			// printf("%I64d%c", f[cur][j], " \n"[j == n]);
		}
	}
	printf("%I64d\n", f[cur][n] == INF ? -1 : f[cur][n]);
	return 0;
}
