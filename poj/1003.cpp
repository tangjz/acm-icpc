#include <cstdio>
#include <cstdlib>
int main()
{
	double s;
	while(scanf("%lf", &s) && s >= 1e-8)
	{
		int n = 1;
		double tmp = 0;
		while(tmp < s) tmp += 1.0 / ++n;
		printf("%d card(s)\n", n - 1);
	}
	return 0;
}