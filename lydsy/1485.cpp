/*
 * 可以证明答案是卡特兰数
 * 有关取模的部分可以分解质因数
 */
#include <cstdio>
int n, p, a[2000001], b[2000001];
long long ans = 1;
long long pow(long long x, long long y)
{
	long long res = 1, sum = x;
	while(y)
	{
		if(y & 1) res = res * sum % p;
		sum = sum * sum % p;
		y >>= 1;
	}
	return res;
}
int main()
{
	scanf("%d%d", &n, &p);
	for(int i = 2; i <= n << 1; ++i)
		if(!a[i])
			for(long long j = (long long)i * i; j <= n << 1; j += i) a[j] = i;
	for(int i = 2; i <= n; ++i) b[i] = -1;
	for(int i = n + 2; i <= n << 1; ++i) b[i] = 1;
	for(int i = n << 1; i >= 2; --i)
		if(!a[i]) ans = ans * pow(i, b[i]) % p;
		else b[a[i]] += b[i], b[i / a[i]] += b[i];
	printf("%lld\n", ans);
	return 0;
}
