#include <cmath>
#include <cstdio>
typedef long long LL;
const int maxn = 10010;
const double pi = acos(-1);
int t, n, x[maxn], y[maxn], d[maxn], r[maxn];
int sqr(int x)
{
	return x * x;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", x + i, y + i);
		x[n] = x[0], y[n] = y[0];
		for(int i = 0; i < n; ++i)
			d[i] = (int)(sqrt(sqr(x[i] - x[i + 1]) + sqr(y[i] - y[i + 1])) + 0.5);
		for(int i = 1; i < n; ++i)
			d[i] -= d[i - 1]; // r[i] = (-1)^i * r[0] + d[i - 1]
		if(n & 1)
		{
			if(d[n - 1] < 0)
			{
				puts("IMPOSSIBLE");
				continue;
			}
			for(int i = 0; i < n; ++i)
				d[i] <<= 1;
			r[0] = d[n - 1] >> 1;
			bool flag = 0;
			for(int i = 1; i < n; ++i)
			{
				r[i] = (i & 1 ? -r[0] : r[0]) + d[i - 1];
				if(r[i] < 0)
				{
					flag = 1;
					break;
				}
			}
			if(flag)
				puts("IMPOSSIBLE");
			else
			{
				LL ans = 0;
				for(int i = 0; i < n; ++i)
					ans += (LL)r[i] * r[i];
				printf("%.2f\n", ans * 0.25 * pi);
				for(int i = 0; i < n; ++i)
					printf("%.2f\n", r[i] * 0.5);
			}
		}
		else
		{
			if(d[n - 1])
			{
				puts("IMPOSSIBLE");
				continue;
			}
			LL sei[3] = {}; //Ax^2+Bx+C
			int Min = 0, Max = d[0];
			sei[0] = n;
			for(int i = 1; i < n; ++i)
			{
				if(i & 1)
				{
					sei[1] -= d[i - 1] << 1;
					if(Max > d[i - 1])
						Max = d[i - 1];
				}
				else
				{
					sei[1] += d[i - 1] << 1;
					if(Min < -d[i - 1])
						Min = -d[i - 1];
				}
				sei[2] += sqr(d[i - 1]);
			}
			if(Min > Max)
			{
				puts("IMPOSSIBLE");
				continue;
			}
			double r0, ans = 0;
			if(sei[0] * Min > -sei[1] / 2)
				r0 = Min;
			else if(sei[0] * Max < -sei[1] / 2)
				r0 = Max;
			else
				r0 = -sei[1] / 2 / (double)sei[0];
			ans = (sei[0] * r0 + sei[1]) * r0 + sei[2];
			printf("%.2f\n%.2f\n", ans * pi, r0);
			for(int i = 1; i < n; ++i)
				printf("%.2f\n", (i & 1 ? -r0 : r0) + d[i - 1]);
		}
	}
	return 0;
}
