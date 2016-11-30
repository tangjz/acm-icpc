#include <stdio.h>
#include <cstring>
const int maxk = 7, maxs = 255, maxd = 26;
int t, tot;
char key[maxk + 1], tmp[maxd], pat[maxd], tex[maxs + 1];
bool vis[maxd];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s ", key);
		memset(vis, 0, sizeof vis);
		tot = 0;
		for(int i = 0; key[i]; ++i)
			if(!vis[key[i] - 'A'])
			{
				pat[tot++] = key[i];
				vis[key[i] - 'A'] = 1;
			}
		int cir = tot;
		for(int i = 0; tot < maxd; ++tot)
		{
			for( ; vis[i]; ++i);
			pat[tot] = 'A' + i;
			vis[i] = 1;
		}
		tot = 0;
		for(int i = 0; i < cir; ++i)
		{
			int k = -1;
			for(int j = 0; j < cir; ++j)
				if(pat[j] && (k == -1 || pat[j] < pat[k]))
					k = j;
			for(int j = 0; j * cir + k < maxd; ++j)
				tmp[tot++] = pat[j * cir + k];
			pat[k] = '\0';
		}
		for(int i = 0; i < maxd; ++i)
			pat[tmp[i] - 'A'] = i + 'A';
		gets(tex);
		for(int i = 0; tex[i]; ++i)
			if(tex[i] >= 'A' && tex[i] <= 'Z')
				tex[i] = pat[tex[i] - 'A'];
		puts(tex);
	}
	return 0;
}
