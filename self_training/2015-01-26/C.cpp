#include <cstdio>
#include <cstring>
const char* out = "BW-";
const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1}, dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int t, chess[8][8], now, cnt[2];
bool rush, vis[8][8];
char str[10];
void fresh()
{
	memset(vis, 0, sizeof vis);
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 8; ++j)
			if(chess[i][j] == 2)
				for(int k = 0; k < 8; ++k)
				{
					int ii = i + dx[k], jj = j + dy[k];
					if(ii < 0 || ii >= 8 || jj < 0 || jj >= 8 || chess[ii][jj] != (now ^ 1))
						continue;
					for(ii += dx[k], jj += dy[k]; ii >= 0 && ii < 8 && jj >= 0 && jj < 8; ii += dx[k], jj += dy[k])
						if(chess[ii][jj] == now)
						{
							vis[i][j] = 1;
							break;
						}
						else if(chess[ii][jj] != (now ^ 1))
							break;
					if(vis[i][j])
						break;
				}
	rush = 1;
}
void cover(int x, int y)
{
	for(int i = 0; i < 8; ++i)
	{
		int xx = x + dx[i], yy = y + dy[i];
		if(xx < 0 || xx >= 8 || yy < 0 || yy >= 8 || chess[xx][yy] != (now ^ 1))
			continue;
		bool flag = 0;
		for(xx += dx[i], yy += dy[i]; xx >= 0 && xx < 8 && yy >= 0 && yy < 8; xx += dx[i], yy += dy[i])
			if(chess[xx][yy] == now)
			{
				flag = 1;
				break;
			}
			else if(chess[xx][yy] != (now ^ 1))
				break;
		if(flag)
			for(xx = x + dx[i], yy = y + dy[i]; xx >= 0 && xx < 8 && yy >= 0 && yy < 8; xx += dx[i], yy += dy[i])
				if(chess[xx][yy] == now)
					break;
				else
				{
					chess[xx][yy] = now;
					++cnt[now];
					--cnt[now ^ 1];
				}
	}
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		rush = cnt[0] = cnt[1] = 0;
		for(int i = 0; i < 8; ++i)
		{
			scanf("%s", str);
			for(int j = 0; j < 8; ++j)
				if(str[j] == 'B')
				{
					chess[i][j] = 0;
					++cnt[0];
				}
				else if(str[j] == 'W')
				{
					chess[i][j] = 1;
					++cnt[1];
				}
				else
					chess[i][j] = 2;
		}
		scanf("%s", str);
		now = str[0] == 'W';
		while(scanf("%s", str) != EOF && str[0] != 'Q')
			if(str[0] == 'L')
			{
				if(!rush)
					fresh();
				bool flag = 0;
				for(int i = 0; i < 8; ++i)
					for(int j = 0; j < 8; ++j)
						if(vis[i][j])
						{
							if(flag)
								putchar(' ');
							else
								flag = 1;
							printf("(%d,%d)", i + 1, j + 1);
						}
				if(!flag)
					printf("No legal move.");
				putchar('\n');
			}
			else
			{
				int x = str[1] - '1', y = str[2] - '1';
				if(!rush)
					fresh();
				if(!vis[x][y])
					now ^= 1;
				chess[x][y] = now;
				cover(x, y);
				++cnt[now];
				rush = 0;
				now ^= 1;
				printf("Black -  %d White -  %d\n", cnt[0], cnt[1]);
			}
		for(int i = 0; i < 8; ++i)
		{
			for(int j = 0; j < 8; ++j)
				str[j] = out[chess[i][j]];
			str[8] = '\0';
			puts(str);
		}
		putchar('\n');
	}
	return 0;
}
