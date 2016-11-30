#include <stdio.h>
const int maxn = 110001;
int tot, prime[maxn], d[maxn];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
			prime[tot++] = d[i] = i;
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
		printf("%d\n", prime[--n]);
	}
	return 0;
}
