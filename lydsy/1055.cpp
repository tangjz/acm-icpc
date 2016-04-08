#include <cstdio>
#include <cstring>
const char* str = "WING";
const int maxn = 210;
int n, m[4];
bool e[4][4][4], f[maxn][maxn][4];
char s[maxn];
int main()
{
	for(int i = 0; i < 4; ++i)
		scanf("%d", m + i);
	for(int i = 0; i < 4; ++i)
	{
		int id[2];
		while(m[i]--)
		{
			scanf("%s", s);
			for(int j = 0; j < 2; ++j)
				for(int k = 0; k < 4; ++k)
					if(s[j] == str[k])
						id[j] = k;
			e[i][id[0]][id[1]] = 1;
		}
	}
	scanf("%s", s);
	n = strlen(s);
	for(int i = 0; i < n; ++i)
		for(int k = 0; k < 4; ++k)
			if(s[i] == str[k])
				f[i][i][k] = 1;
	for(int d = 2; d <= n; ++d)
		for(int i = 0; i <= n - d; ++i)
		{
			int j = i + d - 1;
			for(int k = i; k < j; ++k)
				for(int p = 0; p < 4; ++p)
					for(int q = 0; q < 4; ++q)
						for(int r = 0; r < 4; ++r)
							f[i][j][p] |= e[p][q][r] && f[i][k][q] && f[k + 1][j][r];
		}
	bool flag = 0;
	for(int i = 0; i < 4; ++i)
		if(f[0][n - 1][i])
		{
			flag = 1;
			putchar(str[i]);
		}
	if(!flag)
		puts("The name is wrong!");
	return 0;
}
