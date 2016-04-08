/*
 * w+sÉýÐò wÉýÐòÅÅÐò Ä£Äâ 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int n, sum, ans = -(~0u >> 1);
struct Node { int w, s; } cow[50001];
bool cmp(const Node &x, const Node &y)
{
	if(x.w + x.s != y.w + y.s) return x.w + x.s < y.w + y.s;
	return x.w < y.w;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%d%d", &cow[i].w, &cow[i].s);
	sort(cow, cow + n, cmp);
	for(int i = 0; i < n; ++i)
	{
		if(ans < sum - cow[i].s) ans = sum - cow[i].s;
		sum += cow[i].w;
	}
	printf("%d", ans);
	return 0;
}
