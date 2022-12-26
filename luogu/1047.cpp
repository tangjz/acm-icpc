#include <cstdio>
int L, M, ans, l, r;
bool vis[10001];
int main()
{
	scanf("%d%d", &L, &M);
	while(M--)
	{
		scanf("%d%d", &l, &r);
		while(l <= r) vis[l++] = 1;
	}
	while(L >= 0) ans += vis[L--] ^ 1;
	printf("%d\n", ans);
}
