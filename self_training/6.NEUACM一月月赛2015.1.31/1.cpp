#include <cstdio>
int t;
double a[13], x, tmp;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		for(int i = 0; i < 12; ++i)
			scanf("%lf", a + i);
		for(int i = 0; i < 12; ++i)
		{
			scanf("%lf", &x);
			if(x > a[i])
				a[i] = x;
		}
		for(int i = 0; i < 12; ++i)
		{
			scanf("%lf", &x);
			if(x > a[i])
				a[i] = x;
		}
		scanf("%lf", &x);
		tmp = x;
		for(int i = 0; i < 12; ++i)
			if(a[i] > 0)
				x *= 1 + a[i] / 100;
		printf("%.3f\n", x - tmp);
	}
	return 0;
}
