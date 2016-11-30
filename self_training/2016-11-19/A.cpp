#include <cctype>
#include <stdio.h>
#include <cstring>
const int maxn = 110;
int t, n, m, que[maxn << 2], L, R;
char str[3][maxn];
bool vis[maxn << 2];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		int S = -1;
		for(int i = 0; i < 3; ++i)
		{
			scanf("%s", str[i]);
			int len = strlen(str[i]);
			for(int j = 0; j < len; ++j)
				if(str[i][j] == 's')
				{
					S = (j << 2) + i;
					str[i][j] = '.';
				}
			str[i][len] = str[i][len + 1] = str[i][len + 2] = '\0';
		}
		if(S == -1)
		{
			puts("NO");
			continue;
		}
		memset(vis, 0, sizeof vis);
		L = R = 0;
		que[R++] = S;
		vis[S] = 1;
		while(L < R)
		{
			int udx = que[L++], ux = udx & 3, uy = udx >> 2;
			if(str[ux][uy] == '\0')
				continue;
			if(isalpha(str[ux][uy + 1]))
				continue;
			for(int vx = ux - 1; vx <= ux + 1; ++vx)
			{
				if(vx < 0 || vx >= 3)
					continue;
				int vy = uy;
				for(int j = 0; j < 3; ++j)
					if(isalpha(str[vx][++vy]))
						break;
				if(!isalpha(str[vx][vy]))
				{
					int vdx = (vy << 2) + vx;
					if(!vis[vdx])
					{
						que[R++] = vdx;
						vis[vdx] = 1;
					}
				}
			}
		}
		bool flag = 0;
		for(int i = 0; i < 3; ++i)
		{
			int len = strlen(str[i]);
			for(int j = 0; j < 3; ++j)
				if(vis[((len + j) << 2) + i])
					flag = 1;
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
