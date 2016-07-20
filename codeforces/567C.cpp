#include <cstdio>
const int maxn = 1000010;
int n, now, ans;
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		char op[2];
		int id;
		scanf("%s%d", op, &id);
		if(op[0] == '+')
		{
			vis[id] = 1;
			++now;
		}
		else
		{
			if(!vis[id])
				++ans;
			else
			{
				vis[id] = 0;
				--now;
			}
		}
		if(ans < now)
			ans = now;
	}
	printf("%d\n", ans);
	return 0;
}
