#include <cstdio>
int n;
long long p, q, a;
void swap(long long &x, long long &y)
{
	long long t = x;
	x = y;
	y = t;
}
int main()
{
	scanf("%I64d%I64d%d", &p, &q, &n);
	while(n--)
	{
		scanf("%I64d", &a);
		if(q > p / a)
		{
			puts("NO");
			return 0;
		}
		p -= q * a;
		swap(p, q);
	}
	puts(q ? "NO" : "YES");
	return 0;
}
