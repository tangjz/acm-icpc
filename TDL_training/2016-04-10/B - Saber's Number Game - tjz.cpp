#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 30;
int tt, n, fa[maxn], dig[maxn];
long long ans;
char s[maxn], t[maxn];
bool vis[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d", &tt);
	while(tt--)
	{
		scanf("%d%s%s", &n, s, t);
		for(int i = 0; i < 26; ++i)
		{
			fa[i] = i;
			dig[i] = -1;
			vis[i] = 0;
		}
		ans = 1;
		for(int i = 0; i < n; ++i)
		{
			bool flag1 = s[i] >= '0' && s[i] <= '9';
			bool flag2 = t[i] >= '0' && t[i] <= '9';
			if(flag1 && flag2)
			{
				if(s[i] != t[i])
				{
					ans = 0;
					break;
				}
			}
			else if(!flag1 && !flag2)
			{
				int u = find(s[i] - 'A'), v = find(t[i] - 'A'), digit = -1;
				if(dig[u] != -1)
				{
					if(digit == -1)
						digit = dig[u];
					else if(digit != dig[u])
					{
						ans = 0;
						break;
					}
				}
				if(dig[v] != -1)
				{
					if(digit == -1)
						digit = dig[v];
					else if(digit != dig[v])
					{
						ans = 0;
						break;
					}
				}
				fa[u] = v;
				dig[v] = digit;
			}
			else
			{
				int u = !flag1 ? find(s[i] - 'A') : find(t[i] - 'A'), digit = flag1 ? s[i] - '0' : t[i] - '0';
				if(dig[u] == -1)
					dig[u] = digit;
				else if(dig[u] != digit)
				{
					ans = 0;
					break;
				}
			}
		}
		for(int i = 0; i < n; ++i)
			if(s[i] >= 'A' && s[i] <= 'Z' && dig[find(s[i] - 'A')] != -1)
				s[i] = '0' + dig[find(s[i] - 'A')];
		if(s[0] == '0')
			ans = 0;
		if(!ans)
		{
			puts("0");
			continue;
		}
		if(s[0] >= 'A' && s[0] <= 'Z')
		{
			ans *= 9;
			vis[find(s[0] - 'A')] = 1;
		}
		for(int i = 1; i < n; ++i)
			if(s[i] >= 'A' && s[i] <= 'Z' && !vis[find(s[i] - 'A')])
			{
				ans *= 10;
				vis[find(s[i] - 'A')] = 1;
			}
		cout << ans << endl;
	}
	return 0;
}
