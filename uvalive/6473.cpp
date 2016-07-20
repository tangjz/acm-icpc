#include <cmath>
#include <cstdio>
typedef double DB;
const DB pi = acos(-1.0), x[3] = {0.0, 3.715, 2.894}, y[3] = {0.0, 1.765, -2.115};
int t, id;
DB cl[3], angle[3], A, B, C, D, E, F, delta, xx, yy;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &id);
		A = B = C = D = E = F = 0;
		for(int i = 0; i < 3; ++i)
		{
			scanf("%lf%lf", angle + i, cl + i);
			angle[i] = angle[i] / 180.0 * pi;
			cl[i] += 0.2;
			double ci = cos(angle[i]), si = sin(angle[i]);
			A += cl[i] * 2 * ci * ci;
			B -= cl[i] * 2 * si * ci;
			C -= cl[i] * 2 * ci * si;
			D += cl[i] * 2 * si * si;
			E += cl[i] * 2 * (ci * ci * x[i] - ci * si * y[i]);
			F += cl[i] * 2 * (si * si * y[i] - ci * si * x[i]);
		}
		delta = A * D - B * C;
		xx = (E * D - F * B) / delta;
		yy = (A * F - C * E) / delta;
		printf("%d %.3f %.3f\n", id, xx, yy);
	}
	return 0;
}
