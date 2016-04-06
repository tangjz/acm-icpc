#include <cstdio>
#include <algorithm>
using namespace std;
const int maxk = 1000;
int n, m;
double a[maxk], x, sum, ans, cnt;
int main()
{
	for(int Case = 1; scanf("%d%d", &n, &m) == 2; ++Case)
	{
		if(!n && !m)
			break;
		n *= m;
		for(int i = 0; i < n; ++i)
			scanf("%lf", &a[i]);
		sort(a, a + n);
		scanf("%lf", &x);
		x /= 100;
		sum = ans = cnt = 0;
		bool flag = 0;
		for(int i = 1; i < n; ++i)
		{
			double tmp = (a[i] - a[i - 1]) * i;
			if(tmp + sum > x)
			{
				ans = (x - sum) / i + a[i - 1];
				cnt = i * 100.0 / n;
				break;
			}
			else
				sum += tmp;
		}
		if(!cnt)
		{
			ans = (x - sum) / n + a[n - 1];
			cnt = 100.0;
		}
		printf("Region %d\n", Case);
		printf("Water level is %.2f meters.\n", ans);
		printf("%.2f percent of the region is under water.\n\n", cnt);
	}
	return 0;
}

