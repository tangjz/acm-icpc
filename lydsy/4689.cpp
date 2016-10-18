#include <cmath>
#include <cstdio>
#include <algorithm>
const int maxn = 9;
const double eps = 1e-1;
int d;
double val[maxn], mat[maxn][maxn], sei[maxn];
inline int sgn(double x)
{
	return (x > eps) - (x < -eps);
}
inline int dcmp(double x, double y)
{
	return sgn(x - y);
}
bool gauss()
{
	for(int i = 0; i <= d; ++i)
	{
		int k = i;
		for(int j = i + 1; j <= d; ++j)
			if(dcmp(fabs(mat[j][i]), fabs(mat[j][k])) > 0)
				k = j;
		if(!sgn(mat[k][i]))
			return 0;
		for(int j = i; j <= d + 1; ++j)
			std::swap(mat[i][j], mat[k][j]);
		for(int j = 0; j <= d; ++j)
		{
			if(j == i)
				continue;
			double v = mat[j][i] / mat[i][i];
			for(int k = i; k <= d + 1; ++k)
				mat[j][k] -= v * mat[i][k];
		}
	}
	for(int i = 0; i <= d; ++i)
		sei[i] = mat[i][d + 1] / mat[i][i];
	return 1;
}
int main()
{
	while(scanf("%d", &d) == 1 && d)
	{
		for(int i = 0; i <= d + 2; ++i)
			scanf("%lf", val + i);
		for(int i = 0; i <= d + 2; ++i)
		{
			int mx = i == d + 2 ? d + 1 : d + 2;
			for(int j = 0, o = 0; j <= d + 2; ++j)
			{
				if(j == i || j == mx)
					continue;
				double x = 1;
				for(int k = 0; k <= d; ++k, x *= j)
					mat[o][k] = x;
				mat[o][d + 1] = val[j];
				++o;
			}
			if(gauss())
			{
				double fi = 0, fmx = 0, x = 1, y = 1;
				for(int j = 0; j <= d; ++j, x *= i, y *= mx)
				{
					fi += sei[j] * x;
					fmx += sei[j] * y;
				}
				if(dcmp(fi, val[i]) && !dcmp(fmx, val[mx]))
				{
					printf("%d\n", i);
					break;
				}
			}
		}
	}
	return 0;
}
