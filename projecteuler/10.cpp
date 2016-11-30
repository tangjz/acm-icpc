#include <stdio.h>
const int maxn = 1000001;
int tot, prime[maxn], d[maxn];
long long s[maxn];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		s[i] = s[i - 1];
		if(!d[i])
			s[i] += prime[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * prime[j]) < maxn; ++j)
		{
			d[k] = prime[j];
			if(d[i] == prime[j])
				break;
		}
	}
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%lld\n", s[n]);
	}
	return 0;
}
