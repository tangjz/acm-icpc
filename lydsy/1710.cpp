/*
 * 回文序列的区间动态规划  
 */
#include <cstdio>
template<typename _> inline const _& min(const _& x, const _& y) { return x < y ? x : y; }
int n, m, f[2000][2000], val[26];
char s[2001];
int main()
{
	int i, j, k;
	char ch;
	scanf("%d%d%s", &n, &m, s);
	for(i = 0; i < m; ++i) s[i] -= 'a';
	for(i = 0; i < n; ++i)
	{
		scanf("%*c%c%d%d", &ch, &j, &k);
		val[ch - 'a'] = min(j, k);
	}
	for(i = m - 1; i >= 0; --i)
		for(j = i + 1; j < m; ++j)
			if(s[i] == s[j]) f[i][j] = f[i + 1][j - 1];
			else f[i][j] = min(f[i][j - 1] + val[s[j]], f[i + 1][j] + val[s[i]]);
	printf("%d\n",f[0][m - 1]);
	return 0;
}
