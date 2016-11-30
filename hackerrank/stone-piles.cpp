#include <stdio.h>
#include <cstring>
const int maxn = 51, maxv = 101;
int lim, sg[maxn];
bool vis[maxv];
void dfs(int rem, int last, int Xor)
{
	if(!rem)
	{
		vis[Xor] = 1;
		return;
	}
	for(int i = last + 1; i <= rem && i < lim; ++i)
		dfs(rem - i, i, Xor ^ sg[i]);
}
int main()
{
	memset(sg, -1, sizeof sg);
	sg[1] = 0;
	for(lim = 1; lim < maxn; ++lim)
	{
		memset(vis, 0, sizeof vis);
		dfs(lim, 0, 0);
		for(int j = 0; ; ++j)
			if(!vis[j])
			{
				sg[lim] = j;
				break;
			}
	}
	int t, n, x;
	scanf("%d", &t);
	while(t--)
	{
		int SG = 0;
		scanf("%d", &n);
		while(n--)
		{
			scanf("%d", &x);
			SG ^= sg[x];
		}
		puts(SG ? "ALICE" : "BOB");
	}
	return 0;
}
