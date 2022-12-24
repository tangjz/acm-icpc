#include <cstdio>
int n, x, cnt;
long long sum;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		cnt = sum = 0;
		while(n--)
		{
			scanf("%d", &x);
			if(cnt < x)
				cnt = x;
			sum += x;
		}
		puts(cnt <= sum / 2 ? "YeS" : "No");
	}
	return 0;
}
