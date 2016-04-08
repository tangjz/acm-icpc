#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10010;
int n, p[maxn], q[maxn], r[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d%d", p + i, q + i, r + i);
	sort(p, p + n);
	sort(q, q + n);
	sort(r, r + n);
	int x = p[n >> 1], y = q[n >> 1], z = r[n >> 1];
	long long ret = 0;
	for(int i = 0; i < n; ++i)
	{
		ret += abs(p[i] - x);
		ret += abs(q[i] - y);
		ret += abs(r[i] - z);
	}
	printf("%lld\n", ret);
	return 0;
} 
