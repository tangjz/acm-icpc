#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int t, n, m;
double x, sum;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		m = 0;
		sum = 0;
		scanf("%d", &n);
		for(int i = 0; i < n << 1; ++i)
		{
			scanf("%lf", &x);
			x -= (int)x;
			if(x > eps)
			{
				sum += x;
			}
			else
				++m;
		}
		if(m < n)
			sum -= n - m;
		else
			m = n;
		while(sum - 1 > eps && m)
		{
			sum -= 1;
			--m;
		}
		if(m && abs(sum - 1) < sum)
			sum = abs(sum - 1);
		printf("%.3f\n", abs(sum) + eps);
	}
	return 0;
}
