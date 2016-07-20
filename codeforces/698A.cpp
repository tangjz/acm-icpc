#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110, INF = 0x3f3f3f3f;
int n, a[maxn], f[maxn][3], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for(int i = 1; i <= n; ++i)
		for(int k = 0; k < 3; ++k)
		{
			if(f[i - 1][k] == INF)
				continue;
			// choose 0
			f[i][0] = min(f[i][0], f[i - 1][k] + 1);
			// choose 1
			if(k != 1 && (a[i] & 1))
				f[i][1] = min(f[i][1], f[i - 1][k]);
			// choose 2
			if(k != 2 && (a[i] & 2))
				f[i][2] = min(f[i][2], f[i - 1][k]);
		}
	ans = INF;
	for(int k = 0; k < 3; ++k)
		ans = min(ans, f[n][k]);
	printf("%d\n", ans);
	return 0;
}
