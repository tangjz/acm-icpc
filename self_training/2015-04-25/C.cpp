#include <set>
#include <cstdio>
using namespace std;
const int maxn = 100010;
set<long long> Hash;
int tt, n, t, m, x[maxn], y[maxn], tx[maxn], ty[maxn], mx1[maxn], my1[maxn], mx2[maxn], my2[maxn];
long long cross(int x1, int y1, int x2, int y2)
{
	return (long long)x1 * y2 - (long long)x2 * y1;
}
int main()
{
	scanf("%d", &tt);
	while(tt--)
	{
		Hash.clear();
		scanf("%d%d%d", &n, &t, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", x + i, y + i);
		for(int i = 0; i < t; ++i)
			scanf("%d%d", tx + i, ty + i);
		for(int i = 0; i < m; ++i)
			scanf("%d%d%d%d", mx1 + i, my1 + i, mx2 + i, my2 + i);
		for(int i = 0; i < t; ++i)
		{
			long long tmp = 0;
			for(int j = 0; j < m; ++j)
				if(cross(mx1[j] - tx[i], my1[j] - ty[i], mx2[j] - tx[i], my2[j] - ty[i]) > 0)
					tmp |= 1LL << j;
			Hash.insert(tmp);
		}
		for(int i = 0; i < n; ++i)
		{
			long long tmp = 0;
			for(int j = 0; j < m; ++j)
				if(cross(mx1[j] - x[i], my1[j] - y[i], mx2[j] - x[i], my2[j] - y[i]) > 0)
					tmp |= 1LL << j;
			puts(Hash.count(tmp) ? "1" : "0");
		}
	}
	return 0;
}
