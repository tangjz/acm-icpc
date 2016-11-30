#include <cstdio>
const int maxn = 1000001;
int n, tot, prime[maxn], pos[maxn];
int main()
{
	for(int i = 2; i < maxn; ++i)
		if(!pos[i])
		{
			prime[++tot] = i;
			for(int j = i; j < maxn; j += i)
				pos[j] = tot;
		}
	while(scanf("%d", &n) != EOF)
		printf("%d\n", pos[n]);
	return 0;
}
