/*
 * 能Ac的某种区间dp，但是这个有后效性的，所以数据太弱了
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 501, INF = 0x3f3f3f3f;
int n, cnt, a[maxn], b[maxn], f[maxn][maxn];
int dp(int l, int r)
{
	if(l > r) return INF;
	if(f[l][r] < INF) return f[l][r];
	if(a[l] == a[r]) f[l][r] = min(f[l][r], max(3 - b[l] - b[r], 0) + dp(l + 1, r - 1));
	for(int i = l; i < r; ++i)
		f[l][r] = min(f[l][r], dp(l, i) + dp(i + 1, r));
	return f[l][r];
}
int main()
{
	scanf("%d", &n);
	memset(f, 0x3f, sizeof f);
	for(int i = 1, last = -INF, now; i <= n; ++i)
	{
		scanf("%d", &now);
		if(last != now)
		{
			a[++cnt] = now;
			b[cnt] = 1;
			f[cnt - 1][cnt - 1] = max(3 - b[cnt - 1], 1);
		}
		else ++b[cnt];
		last = now;
	}
	f[cnt][cnt] = max(3 - b[cnt], 1);
	printf("%d\n", dp(1, cnt));
	return 0;
}
