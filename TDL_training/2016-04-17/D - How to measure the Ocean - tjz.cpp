#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 100001;
const double eps = 1e-12;
int n;
pair<int, int> a[maxn];
double d, ans;
int main()
{
	scanf("%lf%d", &d, &n);
	for(int i = 0; i < n; ++i)
	{
		int s, p, o;
		scanf("%d%d%d", &s, &p, &o);
		a[i] = make_pair(s * o, s * p);
	}
	sort(a, a + n, greater<pair<int, int> >());
	int tot = 0;
	for(int i = 0; i < n; ++i)
		if(!i || a[tot - 1].second >= a[i].second)
			a[tot++] = a[i];
	a[tot++] = make_pair(0, 0);
	n = tot;
	ans = a[0].first;
	for(int i = 1; i < n; ++i)
	{
		double delta = (ans - a[i].first) / a[i - 1].second;
		if(delta + eps < d)
		{
			ans = a[i].first;
			d -= delta;
		}
		else
		{
			ans -= d * a[i - 1].second;
			d = 0;
			break;
		}
	}
	if(d < eps)
		printf("%.8f\n", ans);
	else
		puts("0.0");
	return 0;
}
