#include <cstdio>
#include <algorithm>
using namespace std;
int t, n, a[51];
int main()
{
	int i, j, sum;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		sum = 0;
		for(i = 0; i < n; ++i) scanf("%d", &a[i]);
		for(i = 0; i < n; ++i) scanf("%d", &j), a[i] = j - a[i], sum += a[i];
		if(n == 1)
		{
			if(sum > 0) puts("-1");
			else printf("%d\n", -sum);
		}
		else if(n == 2)
		{
			if(sum) puts("-1");
			else printf("%d\n", a[0] >= 0 ? a[0] : -a[0]);
		}
		else if(sum % (n - 2) != 0 || sum < 0) puts("-1");
		else
		{
			sum /= (n - 2);
			for(i = 0; i < n; ++i)
				if(abs(a[i]) > sum || (sum - a[i]) & 1) break;
			if(i < n) puts("-1");
			else printf("%d\n", sum);
		}
	}
	return 0;
}
