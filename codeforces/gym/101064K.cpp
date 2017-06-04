#include <cmath>
#include <cstdio>
const int maxn = 1001;
int n, m;
int main()
{
	double pr = 0;
	scanf("%d", &n);
	for(m = 1; m <= n; ++m)
	{
		pr += log(n + 1 - m) - log(n);
		if(exp(pr) < 0.5 + 1e-15)
			break;
	}
	printf("%d\n", m);
	return 0;
}
