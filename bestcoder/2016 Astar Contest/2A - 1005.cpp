#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL solve(LL n)
{
	LL ret = 0;
	for( ; n > 0; n >>= 1)
		ret += n + 3 >> 2;
	return ret;
}
int t;
LL l, r;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &l, &r);
		printf("%lld\n", solve(r) - solve(l - 1));
	}
	return 0;
}
