#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000001;
int n, que[maxn], pre[maxn], L, R, tot;
bool vis[maxn];
char ans[maxn];
int main()
{
	scanf("%d", &n);
	if(n == 1)
	{
		puts("1");
		return 0;
	}
	que[R] = 1;
	vis[1] = 1;
	pre[R++] = -1;
	while(L < R)
	{
		int p1 = que[L] * 10 % n, p2 = (p1 + 1) % n;
		if(!p1)
		{
			for(int cur = L, nxt = p1; cur != -1; nxt = que[cur], cur = pre[cur])
				ans[tot++] = '0' + (que[cur] * 10 % n != nxt);
			ans[tot++] = '1';
		}
		else if(!vis[p1])
		{
			que[R] = p1;
			vis[p1] = 1;
			pre[R++] = L;
		}
		if(!p2)
		{
			for(int cur = L, nxt = p2; cur != -1; nxt = que[cur], cur = pre[cur])
				ans[tot++] = '0' + (que[cur] * 10 % n != nxt);
			ans[tot++] = '1';
		}
		else if(!vis[p2])
		{
			que[R] = p2;
			vis[p2] = 1;
			pre[R++] = L;
		}
		++L;
	}
	for(int i = 0; i < tot >> 1; ++i)
		swap(ans[i], ans[tot - 1 - i]);
	puts(ans);
	return 0;
}
