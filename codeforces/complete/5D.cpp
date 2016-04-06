#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
double a, v, l, d, w, s1, s2, ans;
int main()
{
	scanf("%lf%lf%lf%lf%lf", &a, &v, &l, &d, &w);
	if(v < w)
		w = v;
	s1 = v * v / a / 2;
	s2 = w * w / a / 2;
	if(d <= s2)
	{
		w = sqrt(2 * a * d);
		ans += w / a;
	}
	else if(d + s2 < 2 * s1)
		ans += (2 * sqrt(a * (d + s2)) - w) / a;
	else
		ans += (2 * v - w) / a + (d + s2 - 2 * s1) / v;
	s1 -= w * w / a / 2;
	if(l - d > s1)
		ans += (v - w) / a + (l - d - s1) / v;
	else
		ans += (sqrt(2 * a * (l - d) + w * w) - w) / a;
	printf("%.14f\n", ans);
	return 0;
}
