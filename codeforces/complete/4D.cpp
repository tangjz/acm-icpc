#include <stack>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, w, h, f[5010], p[5010], pos;
struct gift
{
	int w, h, id;
	bool operator < (const gift &x) const { return w < x.w; }
} a[5010];
int main()
{
	scanf("%d%d%d", &n, &w, &h);
	int nn = n; n = 0;
	for(int i = 1, ww, hh; i <= nn; ++i)
	{
		scanf("%d%d", &ww, &hh);
		if(ww <= w || hh <= h) continue;
		a[++n] = (gift){ww, hh, i};
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
	{
		f[i] = 1;
		for(int j = 1; j < i; ++j)
			if(a[j].w < a[i].w && a[j].h < a[i].h && f[i] < f[j] + 1)
			{
				f[i] = f[j] + 1;
				p[i] = j;
			}
		if(f[pos] < f[i]) pos = i;
	}
	printf("%d\n", f[pos]);
	stack<int> s;
	while(pos)
	{
		s.push(a[pos].id);
		pos = p[pos];
	}
	while(!s.empty())
	{
		printf("%d ", s.top());
		s.pop();
	}
	return 0;
}
