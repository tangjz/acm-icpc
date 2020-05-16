#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxd = 17;
int n, w, Log[maxn], st[maxd][maxn];
int main()
{
	scanf("%d%d", &n, &w);
	for(int i = 2; i <= n; ++i)
		Log[i] = Log[i >> 1] + 1;
	for(int i = 1; i <= n; ++i)
		scanf("%d", st[0] + i);
	for(int d = 1; d <= Log[n]; ++d)
		for(int i = 1; i + (1 << d) - 1 <= n; ++i)
			st[d][i] = max(st[d - 1][i], st[d - 1][i + (1 << d - 1)]);
	for(int i = 1; i <= n; ++i)
	{
		int sum = 0;
		for(int L = 1, R = i; L <= n && sum <= w; L = R + 1, R = min(L + i - 1, n))
		{
			int d = Log[R - L + 1];
			sum += max(st[d][L], st[d][R - (1 << d) + 1]) + (L > 1);
		}
		if(sum <= w)
		{
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
