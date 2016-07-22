#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int N, T;
long long ans, sum;

long long gcd(long long x, long long y)
{
	if(!y)
		return x;
	return gcd(y, x % y);
}

int main()
{
	int t, i, x;
	long long tmp;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		ans = sum = 0;
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d", &x);
			sum += x > 0?x:-x;
			ans += (long long)x * x;
		}
		ans = ans * N - sum * sum;
		tmp = gcd(ans, N);
		printf("%lld/%lld\n", ans / tmp, N / tmp);
	}
	exit(0);
}
