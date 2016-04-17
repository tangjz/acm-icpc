#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1001, maxm = 50001;
int n, m, f[2][maxm];
pair<int, int> a[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i].first, &a[i].second);
	sort(a + 1, a + n + 1);
	int pre = 1, cur = 0;
	memset(f[cur], -1, (m + 1) * sizeof(int));
	f[cur][0] = 0;
	for(int L = 1, R; L <= n; )
	{
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], -1, (m + 1) * sizeof(int));
		for(R = L + 1; R <= n && a[L].first == a[R].first; ++R);
		for( ; L < R; ++L)
			for(int i = m; i >= a[L].second; --i)
			{
				if(f[pre][i - a[L].second] != -1 && f[cur][i] < f[pre][i - a[L].second] + 1)
					f[cur][i] = f[pre][i - a[L].second] + 1;
				if(f[cur][i] < f[cur][i - a[L].second])
					f[cur][i] = f[cur][i - a[L].second];
			}
		for(int i = 0; i <= m; ++i)
			if(f[cur][i] < f[pre][i])
				f[cur][i] = f[pre][i];
	}
	if(f[cur][m] == -1)
		puts("Impossible");
	else
		printf("%d\n", f[cur][m]);
	return 0;
}
