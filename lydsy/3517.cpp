#include <cstdio>
const int maxn = 1001;
int n, row[maxn], col[maxn], ans;
char str[maxn][maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", str[i]);
		for(int j = 0; j < n; ++j)
			if(str[i][j] == '1')
			{
				row[i] ^= 1;
				col[j] ^= 1;
			}
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if((row[i] ^ col[j]) == (str[i][j] == '1'))
				++ans;
	if(ans << 1 > n * n)
		ans = n * n - ans;
	printf("%d\n", ans);
	return 0;
}
