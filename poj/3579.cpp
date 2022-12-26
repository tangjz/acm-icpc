#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, x[maxn];
long long m;
long long cnt(int d)
{
	int L, R, M;
	long long ret = 0;
	for(int i = 0; i < n; ++i)
	{
		L = 0, R = i;
		while(L < R)
		{
			M = L + R >> 1;
			if(d < x[i] - x[M])
				L = M + 1;
			else
				R = M;
		}
		ret += i - L;
		L = i, R = n - 1;
		while(L < R)
		{
			M = L + R + 1 >> 1;
			if(d < x[M] - x[i])
				R = M - 1;
			else
				L = M;
		}
		ret += L - i;
	}
	return ret / 2;
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		m = ((long long)n * (n - 1) / 2 + 1) / 2;
		for(int i = 0; i < n; ++i)
			scanf("%d", x + i);
		sort(x, x + n);
		int L = 0, R = x[n - 1] - x[0], M;
		while(L < R)
		{
			M = L + (R - L >> 1);
			if(cnt(M) < m)
				L = M + 1;
			else
				R = M;
		}
		printf("%d\n", L);
	}
	return 0;
}
