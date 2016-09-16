#include <stdio.h>
#include <algorithm>
typedef long long LL;
int n, x;
LL sum, t1, f1, t2, f2;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		sum += x;
		t1 = std::max(t1 + x, 0LL);
		f1 = std::max(f1, t1);
		t2 = std::max(t2 - x, 0LL);
		f2 = std::max(f2, t2);
	}
	printf("%lld\n", std::max(f1, sum + f2));
	return 0;
}
