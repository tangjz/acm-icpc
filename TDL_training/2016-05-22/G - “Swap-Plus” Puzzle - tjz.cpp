#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 4;
int mat[maxn][maxn], row[maxn], col[maxn], seq[maxn * maxn], ans, out[maxn * maxn << 1], size, tmp[maxn * maxn << 1];
bool vis[maxn * maxn];
int main()
{
	for(int i = 0; i < maxn; ++i)
		for(int j = 0; j < maxn; ++j)
		{
			scanf("%d", mat[i] + j);
			--mat[i][j];
		}
	ans = 25;
	for(int i = 0; i < maxn; ++i)
		row[i] = i;
	do
	{
		for(int i = 0; i < maxn; ++i)
			col[i] = i;
		do
		{
			size = 0;
			memset(vis, 0, maxn * sizeof(bool));
			for(int i = 0; i < maxn; ++i)
				if(!vis[i])
				{
					vis[i] = 1;
					for(int j = row[i]; !vis[j]; j = row[j])
					{
						vis[j] = 1;
						tmp[size++] = (1 << 8) | (j << 4) | (row[j]);
					}
				}
			memset(vis, 0, maxn * sizeof(bool));
			for(int i = 0; i < maxn; ++i)
				if(!vis[i])
				{
					vis[i] = 1;
					for(int j = col[i]; !vis[j]; j = col[j])
					{
						vis[j] = 1;
						tmp[size++] = (2 << 8) | (j << 4) | (col[j]);
					}
				}
			memset(vis, 0, maxn * maxn * sizeof(bool));
			for(int i = 0; i < maxn * maxn; ++i)
				seq[i] = mat[row[i / maxn]][col[i % maxn]];
			for(int i = 0; i < maxn * maxn; ++i)
				if(!vis[i])
				{
					vis[i] = 1;
					for(int j = seq[i]; !vis[j]; j = seq[j])
					{
						vis[j] = 1;
						tmp[size++] = (3 << 8) | (j << 4) | (seq[j]);
					}
				}
			if(ans > size)
			{
				ans = size;
				memcpy(out, tmp, size * sizeof(int));
			}
		} while(next_permutation(col, col + maxn));
	} while(next_permutation(row, row + maxn));
	printf("%d\n", ans);
	for(int i = 0; i < ans; ++i)
		if((out[i] >> 8) == 3)
		{
			reverse(out + i, out + ans);
			break;
		}
	for(int i = 0; i < ans; ++i)
	{
		int typ = out[i] >> 8, x = (out[i] >> 4) & ((1 << 4) - 1), y = out[i] & ((1 << 4) - 1);
		if(typ == 1)
			printf("%c-%c\n", 'a' + x, 'a' + y);
		else if(typ == 2)
			printf("%d-%d\n", 1 + x, 1 + y);
		else
			printf("%c%d-%c%d\n", 'a' + x / maxn, 1 + x % maxn, 'a' + y / maxn, 1 + y % maxn);
	}
	return 0;
}
