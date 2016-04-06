#include <cstdio>
#include <cstring>
int n, p, k, f1, f2;
long double E1, E2, E3, E4, x;
long double pow(long double x, int k)
{
	if(k < 0)
		return 0;
	long double ret = 1.0;
	while(k)
	{
		if(k & 1)
			ret = ret * x;
		x = x * x;
		k >>= 1; 
	}
	return ret;
}
int main()
{
	while(scanf("%d%d%d%d%d", &n, &p, &k, &f1, &f2) == 5)
	{
		E1 = p >= f1 ? (p - f1 + 1.0) / p : 0;
		E2 = p >= f2 ? (p - f2 + 1.0) / p : 0;
		E3 = E1 - E2;
		E4 = 1 - E2;
		x = pow(E1, n);
		if(n > k)
			x += pow(E2, k) * ((n - k) * E4 + 1 - pow(E1, n - k - 1) * ((n - k) * E3 + E1));
		printf("%.3f\n", (double)x);
	}
	return 0;
}
