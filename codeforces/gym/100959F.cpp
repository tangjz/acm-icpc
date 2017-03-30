#include <cstdio>
#include <algorithm>
const int maxn = 21;
int n, m, L[maxn], R[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", L + i, R + i);
	for(int i = 0; i < n; ++i)
	{
		int col = R[i];
		L[m] = L[i];
		for( ; i + 1 < n && R[i + 1] == col; ++i);
		R[m++] = L[i];
		for(int j = i + 1; j < n; ++j)
			if(R[j] == col)
			{
				puts("0");
				return 0;
			}
	}
	if(m == 1)
	{
		puts("-1");
		return 0;
	}
	for(int i = 1, j; i < L[1]; i = j + 1)
	{
		bool flag = 1;
		j = L[1];
		for(int k = 0, cL, cR, pR = -1; k < m; ++k, pR = cR)
		{
			cL = (L[k] - 1) / i;
			cR = (R[k] - 1) / i;
			flag &= pR < cL && cL == cR;
			if(cL)
				j = std::min(j, (L[k] - 1) / cL);
			if(cR)
				j = std::min(j, (R[k] - 1) / cR);
		}
		if(flag)
			ans += j - i + 1;
	}
	printf("%d\n", ans);
	return 0;
}
