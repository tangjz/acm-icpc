#include <cstdio>
const int maxn = 100001;
int n, m, v1, v2, kk, cs;
bool ban(double tim)
{
	double len = m - tim * v1;
	return cs * (len / (v2 - v1)) + (cs - 1) * (len / (v2 + v1)) > tim;
}
int main()
{
	scanf("%d%d%d%d%d", &n, &m, &v1, &v2, &kk);
	cs = (n - 1) / kk + 1;
	double L = 0, R = (double)m / v1, M;
	for(int i = 0; i < 100; ++i)
	{
		M = (L + R) / 2;
		if(ban(M))
			L = M;
		else
			R = M;
	}
	M = (L + R) / 2;
	printf("%.14f\n", M);
	return 0;
}
