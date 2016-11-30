#include <stdio.h>
const int maxn = 71;
const char *buf = "<=>";
int n, m, e[3][maxn][maxn];
long long f[maxn][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int x, y, idx;
		char op[3];
		scanf("%d %s %d", &x, op, &y);
		for(idx = 0; buf[idx]; ++idx)
			if(buf[idx] == op[0])
				break;
		e[idx][x][y] = 1;
		e[2 - idx][y][x] = 1;
		if(op[1] == '=')
			e[1][x][y] = e[1][y][x] = 1;
	}
	for(int i = 1; i + 1 <= n << 1; ++i)
		f[i][i + 1] = e[1][i][i + 1] || !e[0][i][i + 1] && !e[2][i][i + 1];
	for(int sz = 4; sz <= n << 1; sz += 2)
		for(int L = 1, R = sz; R <= n << 1; ++L, ++R)
		{
			// L, L + 1
			{
				bool flag = 1;
				for(int i = L; i <= R && flag; ++i)
					if(i != L && i != L + 1)
						flag &= (!e[1][L][i] || e[0][L][i]) && !e[2][L][i] && (!e[1][L + 1][i] || e[0][L + 1][i]) && !e[2][L + 1][i];
					else
						flag &= (e[1][L][i] || (!e[0][L][i] && !e[2][L][i])) && (e[1][L + 1][i] || (!e[0][L + 1][i] && !e[2][L + 1][i]));
				if(flag)
					f[L][R] += f[L + 2][R];
			}
			// L, R
			{
				bool flag = 1;
				for(int i = L; i <= R && flag; ++i)
					if(i != L && i != R)
						flag &= (!e[1][L][i] || e[0][L][i]) && !e[2][L][i] && (!e[1][R][i] || e[0][R][i]) && !e[2][R][i];
					else
						flag &= (e[1][L][i] || (!e[0][L][i] && !e[2][L][i])) && (e[1][R][i] || (!e[0][R][i] && !e[2][R][i]));
				if(flag)
					f[L][R] += f[L + 1][R - 1];
			}
			// R - 1, R
			{
				bool flag = 1;
				for(int i = L; i <= R && flag; ++i)
					if(i != R - 1 && i != R)
						flag &= (!e[1][R - 1][i] || e[0][R - 1][i]) && !e[2][R - 1][i] && (!e[1][R][i] || e[0][R][i]) && !e[2][R][i];
					else
						flag &= (e[1][R - 1][i] || (!e[0][R - 1][i] && !e[2][R - 1][i])) && (e[1][R][i] || (!e[0][R][i] && !e[2][R][i]));
				if(flag)
					f[L][R] += f[L][R - 2];
			}
		}
	printf("%I64d\n", f[1][n << 1]);
	return 0;
}
