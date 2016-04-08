#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50001;
int n, m, que[maxn], L, R, ans;
bool vis[maxn];
struct Cow
{
	int x, h;
	bool operator < (const Cow &t) const
	{
		return x < t.x;
	}
} p[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &p[i].x, &p[i].h);
	sort(p, p + n);
	for(int i = 0; i < n; ++i)
	{
		while(L < R && p[que[L]].x + m < p[i].x)
			++L;
		if(L == R || p[que[L]].h < p[i].h << 1)
			vis[i] = 1;
		while(L < R && p[que[R - 1]].h <= p[i].h)
			--R;
		que[R++] = i;
	}
	L = R = 0;
	for(int i = n - 1; i >= 0; --i)
	{
		while(L < R && p[que[L]].x - m > p[i].x)
			++L;
		if(L == R || p[que[L]].h < p[i].h << 1)
			vis[i] = 1;
		while(L < R && p[que[R - 1]].h <= p[i].h)
			--R;
		que[R++] = i;
	}
	for(int i = 0; i < n; ++i)
		if(!vis[i])
			++ans;
	printf("%d\n", ans);
	return 0;
}
