#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200;
const double eps = 1e-12;
int n, sz, r;
double p;
long double mat[maxn][maxn];
int main()
{
	scanf("%d%lf", &n, &p);
	sz = 97 << 1;
	mat[0][0] = 1;
	for(int t = 0; t < sz; ++t)
	{
		int i = t >> 1, j = t & 1;
		if(!i || (i <= 25 || i >= 93) && j)
			continue;
		mat[t][t] = 1;
		if(i <= 25)
		{
			mat[t][t + 2] -= 1 - p;
			mat[t][t - 2] -= p;
			mat[t][sz] = 1;
		}
		else if(j & 1)
		{
			//N
			{
				int k = i;
				k += k <= 85;
				mat[t][k << 1] -= 1 - p;
			}
			//Y
			{
				int k = i - 1;
				k -= k + 1 > 25;
				mat[t][k << 1 | k > 25] -= p;
			}
			mat[t][sz] = 1;
		}
		else
		{
			//N??
			{
				int k = i;
				k += k <= 85;
				mat[t][k << 1] -= 1 - p;
				mat[t][sz] += 1 - p;
			}
			//YN?
			{
				int k = i - 1;
				k += k <= 85;
				mat[t][k << 1] -= p * (1 - p);
				mat[t][sz] += 2 * p * (1 - p);
			}
			//YYN
			{
				int k = i - 2;
				k += k <= 85;
				mat[t][k << 1] -= p * p * (1 - p);
				mat[t][sz] += 3 * p * p * (1 - p);
			}
			//YYY
			{
				int k = i - 3;
				k -= k + 1 > 25;
				mat[t][k << 1 | k > 25] -= p * p * p;
				mat[t][sz] += 3 * p * p * p;
			}
		}
	}
	int pos;
	for(int i = 0; i < sz; ++i)
	{
		int k = r;
		for(int j = r + 1; j < sz; ++j)
			if(fabs(mat[j][i]) > fabs(mat[k][i]))
				k = j;
		for(int j = i; j <= sz; ++j)
			swap(mat[r][j], mat[k][j]);
		for(int j = 0; j < sz; ++j)
		{
			if(j == r || fabs(mat[j][i]) < eps)
				continue;
			for(int k = sz; k >= i; --k)
				mat[j][k] = mat[j][k] - mat[j][i] * mat[r][k] / mat[r][i];
		}
		if(i == (n << 1))
			pos = r;
		++r;
	}
	printf("%.10f\n", (double)(mat[pos][sz] / mat[pos][n << 1]));
	return 0;
}
