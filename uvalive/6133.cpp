#include <cstdio>
#include <cstring>
const int maxn = 100010, maxk = 1000010;
struct Trie
{
	int val, ch[26];
} trie[maxk];
int n, tot;
long long ans;
char str[maxk];
void insert()
{
	int o = 0;
	scanf("%s", str);
	for(int i = 0; str[i] != '\0'; ++i)
	{
		str[i] -= 'a';
		if(!trie[o].ch[(int)str[i]])
		{
			//printf("%d -> %d : %c\n", o, tot, str[i] + 'a');
			trie[o].ch[(int)str[i]] = tot++;
		}
		o = trie[o].ch[(int)str[i]];
	}
	++trie[o].val;
}
void dfs(int o, int dep)
{
	ans += (long long)dep * trie[o].val;
	//if(trie[o].val) printf("%d %d\n", dep, trie[o].val);
	int cnt = trie[o].val > 0;
	for(int i = 0; i < 26; ++i)
		if(trie[o].ch[i])
			++cnt;
	for(int i = 0; i < 26; ++i)
		if(trie[o].ch[i])
			dfs(trie[o].ch[i], dep + (cnt > 1));
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		memset(trie, 0, sizeof trie);
		tot = 1;
		ans = 0;
		for(int i = 0; i < n; ++i)
			insert();
		for(int i = 0; i < 26; ++i)
			if(trie[0].ch[i])
				dfs(trie[0].ch[i], 1);
		printf("%.2f\n", (double)ans / n);
	}
	return 0;
}
