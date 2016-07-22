#include <bitset>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100000, maxm = 5000, maxd = 26;
int t, n, m;
bitset<maxm> pos[maxd][3], f[3];
char str[maxn + 10], pat[maxm + 10];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%s%s", &n, &m, str + 1, pat + 1);
		for(int i = 0; i < maxd; ++i)
			pos[i][0].reset();
		for(int i = 1; i <= m; ++i)
		{
			int ch = pat[i] - 'a';
			pos[ch][0].set(i);
		}
		for(int i = 0; i < maxd; ++i)
			for(int j = 1; j < 3; ++j)
				pos[i][j] = pos[i][j - 1] >> 1;
		for(int i = 0; i < 3; ++i)
			f[i].reset();
		f[0].set(0);
		for(int i = 1, cur = 1, nxt = 2; i <= n; ++i, swap(cur, nxt))
		{
			int ch = str[i] - 'a';
			f[nxt] = (f[0] & pos[ch][2]) << 1;
			f[0] = ((f[0] & pos[ch][1]) | (f[cur] & pos[ch][0])) << 1;
			str[i - m + 1] = f[0].test(m) ? '1' : '0';
			f[0].set(0);
		}
		for(int i = n - m + 2; i <= n; ++i)
			str[i] = '0';
		puts(str + 1);
	}
	return 0;
}
