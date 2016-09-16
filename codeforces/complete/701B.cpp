#include <cstdio>
typedef long long LL;
const int maxn = 100001;
int n, m, x, y;
LL cR, cC;
bool row[maxn], col[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	cR = cC = n;
	while(m--)
	{
		scanf("%d%d", &x, &y);
		if(!row[x])
			--cR;
		row[x] = 1;
		if(!col[y])
			--cC;
		col[y] = 1;
		printf("%I64d%c", cR * cC, " \n"[m == -1]);
	}
	return 0;
}
