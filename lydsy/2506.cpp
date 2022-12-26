/*
 * 因为没有修改操作，考虑将询问离线化
 * 将询问转化为从开头到一个点的询问，按照右端点升序排序
 * 一开始序列为空，等到依次处理询问时，将"对以后询问产生影响"的点加入序列，将影响产生
 * 因为询问被排过序，所以只会加点、不会删点，加点操作时间复杂度O(n)
 * 接下来考虑如何产生这个影响
 * 设最大的数为T(不超过10^4)，对于某个询问
 * 当p <= \sqrt{T}时，对于不同的p可以进行分类，所有p值相同的询问可以一次性的扫描中解决
 * 当p > \sqrt{T}时，可以发现不同的Ai值不超过\sqrt{T}个，因此，暴力统计，暴力扫描
 * 总时间复杂度为O(n + m logm \sqrt{T})
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 100001, maxv = 10001, maxsqp = 101;
int n, m, num[maxn], f1[maxsqp][maxsqp], f2[maxv], ans[maxm];
struct Node
{
	int r, f, p, k, id;
	bool operator < (const Node &x) const { return r < x.r; }
} Q[maxm << 1];
int main()
{
	int lim = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", num + i);
		lim = max(lim, num[i]);
	}
	for(int i = 0, l, r, p, k; i < m; ++i)
	{
		scanf("%d%d%d%d", &l, &r, &p, &k);
		Q[i << 1] = (Node){l - 1, -1, p, k, i};
		Q[(i << 1) + 1] = (Node){r, 1, p, k, i};
	}
	sort(Q, Q + (m << 1));
	for(int i = 0, mi = m << 1, now = 0; i < mi; ++i)
	{
		while(now < Q[i].r)
		{
			++now;
			for(int j = 1; j <= 100; ++j)
				++f1[j][num[now] % j];
			++f2[num[now]];
		}
		if(Q[i].p <= 100)
			ans[Q[i].id] += Q[i].f * f1[Q[i].p][Q[i].k];
		else
			for(int j = Q[i].k; j <= lim; j += Q[i].p)
				ans[Q[i].id] += Q[i].f * f2[j];
	}
	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
