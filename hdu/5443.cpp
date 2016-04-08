#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001, maxd = 11;
int t, Log[maxn], n, q, st[maxn][maxd];
int main()
{
	for(int i = 2; i < maxn; ++i)
		Log[i] = Log[i >> 1] + 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", &st[i][0]);
		for(int d = 1; 1 << d <= n; ++d)
			for(int i = 1; i + (1 << d - 1) <= n; ++i)
				st[i][d] = max(st[i][d - 1], st[i + (1 << d - 1)][d - 1]);
		scanf("%d", &q);
		while(q--)
		{
			int L, R, d;
			scanf("%d%d", &L, &R);
			d = Log[R - L + 1];
			printf("%d\n", max(st[L][d], st[R - (1 << d) + 1][d]));
		}
	}
	return 0;
}
