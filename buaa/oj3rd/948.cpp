#include <cstdio>
#include <cstring>
struct Node { char val, ch[3]; } a[30];
char it, str[300], cnt;
void dfs1(char now)
{
	putchar(a[now].val);
	if(a[now].ch[0]) dfs1(a[now].ch[0]);
	if(a[now].ch[1]) dfs1(a[now].ch[1]);
	if(a[now].ch[2]) dfs1(a[now].ch[2]);
}
void dfs2(char now)
{
	if(a[now].ch[0]) dfs2(a[now].ch[0]);
	putchar(a[now].val);
	if(a[now].ch[1]) dfs2(a[now].ch[1]);
	if(a[now].ch[2]) dfs2(a[now].ch[2]);
}
void dfs3(char now)
{
	if(a[now].ch[0]) dfs3(a[now].ch[0]);
	if(a[now].ch[1]) dfs3(a[now].ch[1]);
	putchar(a[now].val);
	if(a[now].ch[2]) dfs3(a[now].ch[2]);
}
void dfs4(char now)
{
	if(a[now].ch[0]) dfs4(a[now].ch[0]);
	if(a[now].ch[1]) dfs4(a[now].ch[1]);
	if(a[now].ch[2]) dfs4(a[now].ch[2]);
	putchar(a[now].val);
}
void build(char now)
{
	if(!str[it]) return;
	a[now].val = str[it++];
	if(str[it] == '(')
	{
		++it;
		if(str[it] != ',')
		{
			a[now].ch[0] = ++cnt;
			build(a[now].ch[0]);
		}
		if(str[it++] == ')') return;
		if(str[it] != ',')
		{
			a[now].ch[1] = ++cnt;
			build(a[now].ch[1]);
		}
		if(str[it++] == ')') return;
		if(str[it] != ')')
		{
			a[now].ch[2] = ++cnt;
			build(a[now].ch[2]);
		}
		++it;
	}
}
int main()
{
	while(scanf("%s", str) != EOF)
	{
		memset(a, 0, sizeof a);
		it = 0;
		cnt = 1;
		build(1);
		printf("PRE: "), dfs1(1), putchar('\n');
		printf("PREMID: "), dfs2(1), putchar('\n');
		printf("POSTMID: "), dfs3(1), putchar('\n');
		printf("POST: "), dfs4(1), putchar('\n');
	}
	return 0;
}
