/*
 * 弦(chord)：连接环中不相邻的两个点的边。
 * 弦图(chordalgraph)：一个无向图称为弦图当且仅当图中任意长度大于3的环都至少有一个弦。
 * 单纯点(simplicialvertex)：设N(v)表示与点v相邻的点集。一个点称为单纯点当{v} + N(v)的诱导子图为一个团。
 * 完美消除序列(perfect elimination ordering)：这是一个序列{v[i]}，它满足v[i]在{v[i..n]}的诱导子图中为单纯点。
 * 弦图的判定：存在完美消除序列的图为弦图。可以用MCS最大势算法求出完美消除序列。
 * 最大势算法 Maximum Cardinality Search
 * 从n到1的顺序依次给点标号(标号为i的点出现在完美消除序列的第i个)。
 * 设label[i]表示第i个点与多少个已标号的点相邻，每次选择label[i]最大的未标号的点进行标号。
 * 判断一个序列是否为完美消除序列
 * 设{vi+1,…,vn}中所有与vi相邻的点依次为vj1,…, vjk。只需判断vj1是否与vj2,…, vjk相邻即可。
 * 本题就是用最少的颜色给每个点染色使得相邻的点染的颜色不同。
 * 完美消除序列从后往前依次给每个点染上可以染的最小的颜色。
 * 拓展：弦图的最大点独立集——完美消除序列从前往后能选就选。最小团覆盖数=最大点独立集数。
 */
#include<cstdio>
int line[2000010], next[2000010], head[10010], f[10010], d[10010], a[10010], c[10010], v[10010];
int n, m, tot = 0, ans = 0;
int main()
{
	int i, j, k, x, y;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= m; ++i)
	{
		scanf("%d%d", &x, &y);
		line[++tot] = y; next[tot] = head[x]; head[x] = tot;
		line[++tot] = x; next[tot] = head[y]; head[y] = tot;
	}
	d[0] = -1;
	for(i = n; i; --i)
	{
		for(k = 0, j = 1; j <= n; ++j) if(!f[j] && d[j] > d[k]) k = j;
		f[k] = i;
		a[i] = k;
		for(j = head[k]; j; j = next[j]) ++d[line[j]];
	}
	for(i = n; i; --i)
	{
		for(j = head[a[i]]; j; j = next[j]) v[c[line[j]]] = i;
		for(j = 1; v[j] == i; ++j);
		c[a[i]] = j;
		if(ans < j) ans = j;
	}
	printf("%d\n", ans);
	return 0;
}
