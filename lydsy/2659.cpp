#include <cstdio>
long long p, q;
int main()
{
	scanf("%lld%lld", &p, &q);
	if(p == q)
		p += 2;
	p >>= 1;
	q >>= 1;
	printf("%lld\n", p * q);
	return 0;
}
