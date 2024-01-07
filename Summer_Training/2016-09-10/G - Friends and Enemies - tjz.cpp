#include <cstdio>
typedef long long LL;
int main()
{
	LL n, m;
	while(scanf("%I64d%I64d", &n, &m) == 2)
		puts(m >= (n >> 1) * (n + 1 >> 1) ? "T" : "F");
	return 0;
}
