#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50002;
int n, m, en, a[maxn];
bool check(int dist)
{
	for(int i = 1, last = 0, now; i < n - m; ++i)
	{
		for(now = last + 1; now < n && a[now] - a[last] < dist; ++now);
		if(now == n)
			return 0;
		last = now;
	}
	return 1;
}
int main()
{
	scanf("%d%d%d", &en, &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	a[n + 1] = en;
	n += 2;
	int l = 0, r = en, mid;
	while(l < r)
	{
		mid = l + r + 1 >> 1;
		if(check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}