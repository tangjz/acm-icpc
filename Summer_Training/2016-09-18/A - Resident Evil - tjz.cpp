#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 3001, maxd = 50;
int n, m;
LL bit[maxn][maxn][4];
void upd(int x, int y, LL val)
{
	for(int i = x; i <= n; i += i & -i)
		for(int j = y; j <= n; j += j & -j)
		{
			bit[i][j][0] ^= val;
			if(x & 1)
				bit[i][j][1] ^= val;
			if(y & 1)
				bit[i][j][2] ^= val;
			if((x & 1) && (y & 1))
				bit[i][j][3] ^= val;
		}
}
LL que(int x, int y)
{
	LL ret = 0;
	for(int i = x; i > 0; i -= i & -i)
		for(int j = y; j > 0; j -= j & -j)
		{
			if(!(x & 1) && !(y & 1))
				ret ^= bit[i][j][0];
			if(!(y & 1))
				ret ^= bit[i][j][1];
			if(!(x & 1))
				ret ^= bit[i][j][2];
			ret ^= bit[i][j][3];
		}
	return ret;
}
inline void scan(int &x)
{
	register int ch;
	while((ch = getchar()) < '0' || ch > '9');
	for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= n; ++i)
			memset(bit[i] + 1, 0, (n << 2) * sizeof(LL));
		while(m--)
		{
			char op[2];
			int x1, y1, x2, y2;
			LL mask = 0;
			scanf("%s", op); scan(x1); scan(y1); scan(x2); scan(y2);
			if(x1 > x2)
				std::swap(x1, x2);
			if(y1 > y2)
				std::swap(y1, y2);
			if(op[0] == 'P')
			{
				int k, a, b;
				scan(k);
				while(k--)
				{
					scan(a); scan(b);
					if(b & 1)
						mask ^= 1LL << --a;
				}
				upd(x1, y1, mask);
				upd(x2 + 1, y1, mask);
				upd(x1, y2 + 1, mask);
				upd(x2 + 1, y2 + 1, mask);
			}
			else
			{
				mask = que(x2, y2) ^ que(x1 - 1, y2) ^ que(x2, y1 - 1) ^ que(x1 - 1, y1 - 1);
				for(int i = 0; i < maxd; ++i)
					printf("%d ", (mask >> i) & 1 ? 2 : 1);
				putchar('\n');
			}
		}
	}
	return 0;
}
