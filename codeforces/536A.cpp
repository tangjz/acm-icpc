#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 10010, mod = 1000000007;
int q, l, t, m;
long long a, b;
long long f(long long x)
{
	return a + (x - 1) * b;
}
long long s(long long l, long long r)
{
	return (f(l) + f(r)) * (r - l + 1) / 2;
}
int main()
{
	scanf("%I64d%I64d%d", &a, &b, &q);
	while(q--)
	{
		scanf("%d%d%d", &l, &t, &m);
		long long L = l - 1, R = 3e6;
		while(L < R)
		{
			long long M = L + R + 1 >> 1;
			if(f(M) > t || s(l, M) > (long long)t * m)
				R = M - 1;
			else
				L = M;
		}
		printf("%I64d\n", L < l ? -1 : L);
	}
	return 0;
}
