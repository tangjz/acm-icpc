/*
 * 平方可以认为是做了两遍游戏各种结果的有序对个数
 * 令f[i,j,k,l]表示第一次游戏上面取i个，下面取j个，第二次游戏上面取k个，下面取l个的答案
 * 因为时刻要求i+j=k+l，所以可以消掉一维，连同转移的复杂度
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 502, mod = 1024523;
int n, m, f[maxn][maxn][maxn];
char s[maxn], t[maxn];
inline void upd(int &x, const int &y)
{
	x += y;
	if(x >= mod) x -= mod;
}
int main()
{
	scanf("%d%d%s%s", &n, &m, s, t);
	f[0][0][0] = 1;
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= m; ++j)
			for(int k = 0; k <= n; ++k)
				if(f[i][j][k])
				{
					int l = i + j - k;
					if(s[i] == s[k]) upd(f[i + 1][j][k + 1], f[i][j][k]);
					if(s[i] == t[l]) upd(f[i + 1][j][k], f[i][j][k]);
					if(t[j] == s[k]) upd(f[i][j + 1][k + 1], f[i][j][k]);
					if(t[j] == t[l]) upd(f[i][j + 1][k], f[i][j][k]);
				}
	printf("%d\n", f[n][m][n]);
	return 0;
}
