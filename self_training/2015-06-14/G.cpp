#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 500001, INF = ~0u >> 1;
int n, a[maxn], L, R, M;
long long cnt;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		L = 0, R = INF;
		while(L < R)
		{
			M = L + (R - L >> 1);
			cnt = 0;
			for(int i = 0, j = 0; i < n; ++i)
			{
				for( ; j < i && a[i] - a[j] > M; ++j);
				cnt += i - j;
			}
			if(cnt >= n * (n - 1LL) + 2 >> 2)
				R = M;
			else
				L = M + 1;
		}
		printf("%d\n", L);
	}
	return 0;
}
