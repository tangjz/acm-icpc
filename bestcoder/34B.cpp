#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 50010;
int n, w, h, a[maxn], d[maxn * 3];
long long sum, sum1, sum2, ans;
void scan(int &x)
{
	int ch = 0;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
}
int main()
{
	while(scanf("%d%d%d", &n, &w, &h) == 3)
	{
		sum = sum1 = sum2 = 0;
		for(int i = 0; i < n; ++i)
		{
			scan(a[i]);
			sum += a[i];
		}
		if(sum < (long long)w * h)
		{
			puts("-1");
			continue;
		}
		for(int i = 0; i < w; ++i)
			d[i] = -h;
		for(int i = 0; i < n; ++i)
			d[w + i] = a[i] - h;
		for(int i = 0; i < w; ++i)
			d[w + n + i] = -h;
		ans = (long long)1e12;
		for(int i = 0, j = 0; i < w + n; ++i)
		{
			while(j < i + w)
			{
				if(d[j] > 0)
					sum1 += d[j];
				else
					sum2 -= d[j];
				++j;
			}
			ans = min(ans, max(sum1, sum2));
			if(d[i] > 0)
				sum1 -= d[i];
			else
				sum2 += d[i];
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
