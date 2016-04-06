#include <cstdio>
const int maxs = 501, mod = 10007, inv6 = 1668;
int n;
char str[maxs];
int main()
{
	scanf("%s", str);
	for(int i = 0; str[i]; ++i)
		n = ((n << 3) + (n << 1) + str[i] - '0') % mod;
	printf("%d\n", n * (n + 1LL) * (n + 2) * inv6 % mod);
	return 0;
}
