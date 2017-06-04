#include <stdio.h>
#include <algorithm>
using namespace std;
#define x first
#define y second
typedef long long LL;
const int maxn = 100001, maxm = 100001;
int t, n;
pair<int, int> p[maxn];
bool check(int r)
{
	int xL = -maxm, xR = maxm, yL = -maxm, yR = maxm, zL = -maxm << 1, zR = maxm << 1;
	for(int i = 0; i < n; ++i)
	{
		xL = max(xL, p[i].x - r);
		xR = min(xR, p[i].x + r);
		yL = max(yL, p[i].y - r);
		yR = min(yR, p[i].y + r);
		zL = max(zL, p[i].x + p[i].y - r);
		zR = min(zR, p[i].x + p[i].y + r);
	}
	if(xL > xR || yL > yR)
		return 0;
	zL = max(zL, xL + yL);
	zR = min(zR, xR + yR);
	return zL <= zR;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &p[i].x, &p[i].y);
		int L = 0, R = maxm;
		while(L < R)
		{
			int M = (L + R) >> 1;
			if(check(M))
				R = M;
			else
				L = M + 1;
		}
		LL ans = L * (L + 1LL) * 3 + 1;
		printf("Case %d: %lld\n", Case, ans);
	}
	return 0;
}
