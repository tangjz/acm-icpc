#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 21, maxm = 26;
int n, m, c[maxn][maxm], id[maxn], f[1 << maxn];
char str[maxn][maxm], que[maxn];
bool cmp(const int &x, const int &y)
{
	return que[x] < que[y];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", str[i]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", c[i] + j);
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			que[j] = str[j][i];
			id[j] = j;
		}
		sort(id, id + n, cmp);
		for(int j = 0, k; j < n; j = k)
		{
			for(k = j + 1; k < n && que[id[k - 1]] == que[id[k]]; ++k);
			int w = 0, tmp = 0, o = 0;
			for(int t = j; t < k; ++t)
			{
				w += c[id[t]][i];
				if(tmp < c[id[t]][i])
					tmp = c[id[t]][i];
				o |= 1 << id[t];
			}
			w -= tmp;
			for(int s = 0; s < 1 << n; ++s)
				if(f[s | o] > f[s] + w)
					f[s | o] = f[s] + w;
			for(int t = j; t < k; ++t)
			{
				w = c[id[t]][i];
				o = 1 << id[t];
				for(int s = 0; s < 1 << n; ++s)
					if(f[s | o] > f[s] + w)
						f[s | o] = f[s] + w;
			}
		}
	}
	printf("%d\n", f[(1 << n) - 1]);
	return 0;
}
