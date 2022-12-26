#include <stdio.h>
#include <cstring>
const int maxn = 5001;
int n, a[maxn], f[maxn][maxn], Lmx[maxn], Rmx[maxn];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		memset(Lmx + 1, 0, n * sizeof(int));
		memset(Rmx + 1, 0, n * sizeof(int));
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int len = 1; len <= n; ++len)
			for(int L = 1, R = len; R <= n; ++L, ++R)
				if(a[L] == a[R])
					f[L][R] = 0;
				else if(a[L] < a[R])
				{
					f[L][R] = Lmx[L] + 1;
					if(Rmx[R] < f[L][R])
						Rmx[R] = f[L][R];
				}
				else
				{
					f[L][R] = Rmx[R] + 1;
					if(Lmx[L] < f[L][R])
						Lmx[L] = f[L][R];
				}
		for(int i = 1; i <= n; ++i)
			printf("%d%c", Lmx[i] < Rmx[i] ? Rmx[i] : Lmx[i], " \n"[i == n]);
	}
	return 0;
}
