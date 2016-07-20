#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10010, maxt = 10000010, maxs = 1010;
int t, m, w, last, ans, tot, seq[maxn];
bool vis[maxt];
char str[maxs];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		last = ans = 0;
		memset(vis, 0, sizeof vis);
		vis[0] = 1;
		scanf("%d%d\n", &m, &w);
		while(m--)
		{
			tot = 0;
			gets(str);
			for(int i = 0; str[i]; ++i)
			{
				for(int j = 0, k = 0; j < 7 && str[i + j]; ++j)
				{
					if(str[i + j] < '0' || str[i + j] > '9')
						break;
					k = (k << 3) + (k << 1) + (str[i + j] - '0');
					if(!vis[k])
						seq[tot++] = k;
				}
			}
			sort(seq, seq + tot);
			for(int i = 0; i < tot; ++i)
				if(seq[i] <= last + w && !vis[seq[i]])
					for(vis[seq[i]] = 1; vis[last + 1]; ++last);
		}
		for(int i = w; i >= 0; --i)
			if(vis[last + i])
			{
				ans = last + i;
				break;
			}
		printf("Case %d: %d %d\n", Case, last, ans);
	}
	return 0;
}
