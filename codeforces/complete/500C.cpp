#include <cstdio>
#include <algorithm>
using namespace std;
long long n, m, w[666], b[2333], seq[666], vis[666], ans;
int main()
{
	scanf("%I64d%I64d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%I64d", &w[i]);
	for(int i = 1; i <= m; ++i)
		scanf("%I64d", &b[i]);
	for(int i = 1, j = n; j > 0; --j)
	{
		while(i <= m && vis[b[i]])
			++i;
		if(i <= m)
		{
			seq[j] = b[i];
			vis[b[i]] = 1;
		}
		else
			break;
	}
	for(int i = 1; i <= m; ++i)
	{
		int j;
		for(j = 1; j <= n; ++j)
			if(seq[j] == b[i])
				break;
		for(int k = j + 1; k <= n; ++k)
			ans += w[seq[k]];
		for(int k = j + 1; k <= n; ++k)
			seq[k - 1] = seq[k];
		seq[n] = b[i];
	}
	printf("%I64d\n", ans);
	return 0;
}

