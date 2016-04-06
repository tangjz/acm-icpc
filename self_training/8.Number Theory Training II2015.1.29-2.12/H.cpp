#include <cstdio>
const int maxn = 1e6 + 10, maxk = 1001;
int t, n, s[maxn];
bool vis[maxn];
int main()
{
	for(int i = 1; i * 2 < maxn; ++i)
		for(int j = i * 2; j < maxn; j += i)
			s[j] += i;
	for(int i = 1; i < maxn; ++i)
		if(s[i] < maxk)
			vis[s[i]] = 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		puts(vis[n] ? "no" : "yes");
	}
	return 0;
}
