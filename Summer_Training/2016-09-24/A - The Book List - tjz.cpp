#include <set>
#include <map>
#include <string>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 3010, maxs = 110;
int tot;
struct Trie
{
	map<string, int> nxt;
	set<string> leaf;
} e[maxn];
char str[maxs];
int newnode()
{
	map<string, int>().swap(e[tot].nxt);
	set<string>().swap(e[tot].leaf);
	return tot++;
}
void dfs(int u, int dep)
{
	for(map<string, int>::iterator it = e[u].nxt.begin(); it != e[u].nxt.end(); ++it)
	{
		for(int i = 0; i < dep << 2; ++i)
			putchar(' ');
		printf("%s\n", (it -> first).c_str());
		dfs(it -> second, dep + 1);
	}
	for(set<string>::iterator it = e[u].leaf.begin(); it != e[u].leaf.end(); ++it)
	{
		for(int i = 0; i < dep << 2; ++i)
			putchar(' ');
		printf("%s\n", (*it).c_str());
	}
}
int main()
{
	for(int Case = 1; gets(str); ++Case)
	{
		tot = 0;
		newnode();
		do
		{
			int len = strlen(str), i, p, rt = 0;
			for(i = 0, p = -1; i < len; ++i)
				if(str[i] == '/')
				{
					str[i] = '\0';
					string edge = str + p + 1;
					if(!e[rt].nxt.count(edge))
						e[rt].nxt[edge] = newnode();
					rt = e[rt].nxt[edge];
					str[i] = '/';
					p = i;
				}
			string book = str + p + 1;
			e[rt].leaf.insert(book);
			gets(str);
		} while(strcmp(str, "0"));
		printf("Case %d:\n", Case);
		dfs(0, 0);
	}
	return 0;
}
