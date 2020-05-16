#include <stdio.h>
#include <cstring>
const int maxn = 101;
int t, n, perm[maxn], sp, f[2][maxn][maxn];
int F(int m, int L, int R)
{
	int &ret = f[m][L][R];
	if(ret >= 0)
		return ret;
	if(L == R)
		return ret = 1;
	ret = !m || F(0, L, R);
	for(int i = L; i <= R; ++i)
		if((i == L || perm[i - 1] < perm[i]) && (i == R || perm[i + 1] < perm[i]))
			ret &= sp < i ? F((m + R - i) & 1, L, i - 1) : F((m + i - L) & 1, i + 1, R);
	return ret ^= 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", perm + i);
			if(perm[i] == 1)
				sp = i;
			memset(f[0][i] + 1, -1, n * sizeof(int));
			memset(f[1][i] + 1, -1, n * sizeof(int));
		}
		puts(F(0, 1, n) ? "Alice" : "Bob");
	}
	return 0;
}
