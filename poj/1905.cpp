#include <cmath>
#include <cstdio>
const double eps = 1e-4;
double l, n, c, s, r, L, R, M;
int main()
{
	while(scanf("%lf%lf%lf", &l, &n, &c) == 3)
	{
		if(l < 0 && n < 0 && c < 0)
			break;
		s = (1 + n * c) * l;
		L = 0, R = l / 2;
		while(R - L >= eps)
		{
			M = (L + R) / 2;
			r = (4 * M * M + l * l) / (8 * M);
			if(2 * r * asin(l / (2 * r)) < s)
				L = M;
			else
				R = M;
		}
		printf("%.3f\n", L);
	}
	return 0;
}