#include <cstdio>
#include <cstring>
const int maxn = 101, maxd = 10, trv[maxd] = {14, 1, 5, 3, 11, 9, 7, 15, 13, 6};
int tri[1 << 6], n, val[maxn];
char op[2], str[maxn << 2];
int main()
{
	memset(tri, -1, sizeof tri);
	for(int i = 0; i < maxd; ++i)
		tri[trv[i]] = i;
	while(scanf("%d", &n) == 1 && n)
	{
		scanf("%s", op);
		if(op[0] == 'S')
		{
			scanf("%s", str);
			for(int i = 0; i < n; ++i)
				val[i] = trv[str[i] - '0'];
			for(int i = 0; i < 3; ++i)
			{
				for(int j = 0; j < n; ++j)
				{
					for(int k = 0; k < 2; ++k)
						str[j * 3 + k] = (val[j] & (1 << (i << 1 | k))) ? '*' : '.';
					str[j * 3 + 2] = j < n - 1 ? ' ' : '\0';
				}
				puts(str);
			}
		}
		else
		{
			memset(val, 0, n * sizeof(int));
			for(int i = 0; i < 3; ++i)
				for(int j = 0; j < n; ++j)
				{
					scanf("%s", str);
					for(int k = 0; k < 2; ++k)
						if(str[k] == '*')
							val[j] |= 1 << (i << 1 | k);
				}
			for(int i = 0; i < n; ++i)
				str[i] = '0' + tri[val[i]];
			str[n] = '\0';
			puts(str);
		}
	}
	return 0;
}
