#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n = 0, limit_time, t[101], v[101], l[101] = {}, r[101] = {}, f[101][121];
void make_tree()
{
	int now = ++n;
	scanf("%d%d", &t[now], &v[now]);
	if(!v[now])
	{
		l[now] = n + 1; make_tree();
		r[now] = n + 1; make_tree();
	}
}
void dp(int now)
{
	if(!now) return;
	if(v[now])
	{
		f[now][0] = 0; f[now][1] = t[now] * 2 + 5;
		for(int i = 2; i <= v[now]; ++i) f[now][i] = f[now][i - 1] + 5;
		return;
	}
	dp(l[now]);
	dp(r[now]);
	f[now][0] = 0;
	for(int i = 1; i <= 120; ++i)
		for(int j = 0; j <= i; ++j)
			f[now][i] = min(f[now][i], f[l[now]][j] + f[r[now]][i - j] + t[now] * 2);
}
int main()
{
	int i;
	scanf("%d", &limit_time);
	memset(f, 0xf, sizeof(f));
	make_tree();
	dp(1);
	for(i = 120; i; --i) if(f[1][i] < limit_time) break;
	printf("%d\n", i);
	return 0;
}
