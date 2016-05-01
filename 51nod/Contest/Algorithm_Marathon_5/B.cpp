#include <cstdio>
const int maxn = 1 << 4, maxs = 4;
int n, h[maxn];
long long v[maxn];
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		int x, w;
		scanf("%d%d", &x, &w);
		v[x] = w;
	}
	for(int i = 0; i < maxs; ++i)
		h[1 << i] = 1 << i;
	for(int i = 2; i < maxn; i += 2)
		v[i] -= v[0];
	for(int i = 1; i < maxn; ++i)
		if(!h[i])
		{
			h[i] = h[i - 1];
			v[i] -= v[i ^ h[i]];
		}
	for(int i = 0; i < maxn; ++i)
		printf("%d%c", v[i], " \n"[i == maxn - 1]);
	return 0;
}
