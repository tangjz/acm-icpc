#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;
int n, g[30][30], cnt;
bool flag, vis[30];
char name[110][110], ans[30];
int main()
{
	scanf("%d%s", &n, name[0]);
	for(int i = 1; i < n; ++i)
	{
		scanf("%s", name[i]);
		int j;
		for(j = 0; name[i - 1][j] != '\0' && name[i - 1][j] == name[i][j]; ++j);
		if(name[i - 1][j] && !name[i][j])
		{
			puts("Impossible");
			return 0;
		}
		if(name[i - 1][j] != '\0' && name[i][j] != '\0')
			g[name[i - 1][j] - 'a'][name[i][j] - 'a'] = 1;
	}
	for(int i = 0; i < 26; ++i)
	{
		int j;
		for(j = 0; j < 26; ++j)
			if(!vis[j])
			{
				int k;
				for(k = 0; k < 26; ++k)
					if(g[k][j])
						break;
				if(k >= 26)
					break;
			}
		if(j >= 26)
			break;
		vis[j] = 1;
		ans[cnt++] = 'a' + j;
		for(int k = 0; k < 26; ++k)
			g[j][k] = 0;
	}
	if(cnt != 26)
		puts("Impossible");
	else
		puts(ans);
	return 0;
}
