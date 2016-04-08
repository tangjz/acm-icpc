#include <cstdio>
typedef long long LL;
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
int main()
{
	int A, B, C;
	scanf("%d%d%d", &A, &B, &C);
	printf("%d\n", mod_pow(A, B, C));
	return 0;
}
