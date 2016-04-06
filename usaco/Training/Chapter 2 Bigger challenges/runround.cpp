/*
ID: tangjin2
LANG: C++
TASK: runround
*/
#include <cstdio>
#include <cstring>
int ans;
bool check()
{
	char tmp[10] = {};
	sprintf(tmp, "%d", ans);
	int i, flag = 0, len = strlen(tmp);
	bool used[10] = {}, vis[10] = {};
	for(i = 0; i < len; ++i)
		if(used[(int)tmp[i] - '0']) return 0;
		else used[(int)tmp[i] - '0'] = 1;
	for(i = 0; i < len; ++i)
	{
		flag = (flag + tmp[flag] - '0') % len;
		if(vis[flag]) return 0;
		vis[flag] = 1;
	}
	return 1;
}
int main()
{
	freopen("runround.in", "r", stdin);
	freopen("runround.out", "w", stdout);
	scanf("%d", &ans);
	while(++ans)
		if(check())
		{
			printf("%d\n", ans);
			break;
		}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
