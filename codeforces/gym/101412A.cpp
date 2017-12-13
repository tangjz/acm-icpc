#include <cstdio>
#include <algorithm>
const int maxn = 20001;
int tot, prime[maxn], t, n, m;
bool vis[maxn];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) < maxn; ++j)
		{
			vis[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if((n = std::abs(n)) < (m = std::abs(m)))
			std::swap(n, m);
		puts((m ? !vis[n * n + m * m] : (n & 3) == 3 && !vis[n]) ? "P" : "C");
	}
	return 0;
}
