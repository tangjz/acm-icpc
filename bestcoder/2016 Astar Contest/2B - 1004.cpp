#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000010, INF = 0x3f3f3f3f;
int n, m, l[maxn], r[maxn];
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d", l + i, r + i);
			if(l[i] > r[i])
				swap(l[i], r[i]);
		}
		int L = 0, R = n - 1;
		while(L < R)
		{
			int M = L + R >> 1, v[4] = {-INF, INF, -INF, INF};
			for(int i = 0; i < m; ++i)
				if(r[i] - l[i] > M)
				{
					v[0] = max(v[0], l[i] + r[i] - M);
					v[1] = min(v[1], l[i] + r[i] + M);
					v[2] = max(v[2], r[i] - l[i] - M);
					v[3] = min(v[3], r[i] - l[i] + M);
				}
			if(v[0] <= v[1] && v[2] <= v[3])
				R = M;
			else
				L = M + 1;
		}
		printf("%d\n", L);
	}
	return 0;
}
