#include <cstdio>
int L, a, b, c;
double x[8], y[8], z[8], xx, yy, zz;
int main()
{
	while(scanf("%d", &L) != EOF)
	{
		xx = yy = zz = 0;
		for(int i = 0; i < 8; ++i)
			scanf("%lf%lf%lf", x + i, y + i, z + i);
		scanf("%d%d%d", &a, &b, &c);
		x[1] -= x[0], x[2] -= x[0], x[4] -= x[0];
		y[1] -= y[0], y[2] -= y[0], y[4] -= y[0];
		z[1] -= z[0], z[2] -= z[0], z[4] -= z[0];
		xx = x[1] * a / L + x[2] * b / L + x[4] * c / L + x[0];
		yy = y[1] * a / L + y[2] * b / L + y[4] * c / L + y[0];
		zz = z[1] * a / L + z[2] * b / L + z[4] * c / L + z[0];
		printf("%.3f %.3f %.3f\n", xx, yy, zz);
	}
	return 0;
}
