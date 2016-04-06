#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int t, n, m, a[maxn], b[maxn];
long long c[maxn];
bool check(int s)
{
	for(int i = 0; i < n; ++i)
		c[i] = a[i] + (long long)b[i] * s;
	sort(c, c + n);
	long long ret = 0;
	for(int i = 0; i < s; ++i)
		ret += c[i];
	return ret <= m;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < n; ++i)
			scanf("%d", b + i);
		int L = 0, R = n;
		while(L < R)
		{
			int M = L + R + 1 >> 1;
			if(check(M))
				L = M;
			else 
				R = M - 1;
		}
		printf("%d\n", L);
	}
	return 0;
}
