#include <cstdio>
const int maxx = 16001;
int tot, prime[maxx];
bool vis[maxx];
int main()
{
	for(int i = 2; i < maxx; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && i * prime[j] < maxx; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	vis[1] = vis[2] = 1;
	for(int Case = 1, x; scanf("%d", &x) != EOF && x > 0; ++Case)
		printf("%d: %s\n", Case, vis[x] ? "no" : "yes");
	return 0;
}
