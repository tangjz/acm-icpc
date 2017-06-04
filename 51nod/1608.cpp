#include <stdio.h>
const int maxn = 500001, mod = 1000003;
int n, m, row[maxn], col[maxn], ways;
char buf[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", buf);
		for(int j = 0; j < m; ++j)
		{
			if(buf[j] == '.')
				continue;
			int typ = buf[j] - '1', hor = typ >> 1, ver = (typ & 1) ^ hor;
			if(!row[i])
				row[i] = (hor ^ (j & 1)) + 1;
			else if(row[i] != (hor ^ (j & 1)) + 1)
			{
				puts("0");
				return 0;
			}
			if(!col[j])
				col[j] = (ver ^ (i & 1)) + 1;
			else if(col[j] != (ver ^ (i & 1)) + 1)
			{
				puts("0");
				return 0;
			}
		}
	}
	ways = 1;
	for(int i = 0; i < n; ++i)
		!row[i] && (ways <<= 1) >= mod && (ways -= mod);
	for(int i = 0; i < m; ++i)
		!col[i] && (ways <<= 1) >= mod && (ways -= mod);
	printf("%d\n", ways);
	return 0;
}
