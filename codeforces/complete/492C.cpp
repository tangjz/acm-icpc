#include <cstdio>
#include <algorithm>
using namespace std;
int n, r, avg;
long long res, ans;
struct Node
{
	int a, b;
	bool operator < (const Node &x) const
	{ return b < x.b; }
} e[233333];
int main()
{
	scanf("%d%d%d", &n, &r, &avg);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", &e[i].a, &e[i].b);
		e[i].a = avg - e[i].a;
		res += e[i].a;
	}
	sort(e, e + n);
	for(int i = 0; i < n && res > 0; ++i)
		if(e[i].a + r - avg > 0)
		{
			long long k = min(res, (long long)e[i].a + r - avg);
			res -= k;
			ans += k * e[i].b;
		}
	printf("%I64d\n", ans);
	return 0;
}
