#include <cmath>
#include <stdio.h>
const int maxt = 100;
const double pi = acos(-1), eps = 1e-9;
double s;
int dcmp(double x)
{
	return (x > eps) - (x < -eps);
}
double calc(double r)
{
	double l = s / r / pi - r;
	double h = sqrt(l * l - r * r);
	return pi * r * r * h / 3;
}
int main()
{
	scanf("%lf", &s);
	double L = 0, R = sqrt(s / 2 / pi);
	for(int i = 0; i < maxt; ++i)
	{
		double ML = L + (R - L) / 3, MR = R - (R - L) / 3;
		if(dcmp(calc(ML) - calc(MR)) > 0)
			R = MR;
		else
			L = ML;
	}
	printf("%.6f\n", calc(L));
	return 0;
}
