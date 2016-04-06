#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2001;
int n, x[maxn], w[maxn];
long long ans;
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", x + i);
	for(int i = 1; i <= n; ++i)
	{
		int r = 0;
		for(int j = 1; j <= n; ++j)
			if(!vis[j] && w[r] <= w[j])
				r = j;
		vis[r] = 1;
		ans += w[r];
		for(int j = 1; j <= n; ++j)
			if(w[j] < (x[r] ^ x[j]))
				w[j] = x[r] ^ x[j];
	}
	printf("%lld\n", ans);
	return 0;
}
