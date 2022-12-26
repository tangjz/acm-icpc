/*
 * 用到的概率公式
 * P(A + B) = P(A) + P(B) - P(A) * P(B)
 * P(A) = [P(A + B) - P(B)] / [1 - P(B)] 注意P(B)为1的情况
 * 设f[i]表示i被充电的概率，g[i]表示i被以i为根的子树充电的概率
 * 关于g[]，g[i]应该为自己充电的概率和儿子们对其充电的概率的并集
 * 关于f[]，考虑一条边e的父亲是u，儿子是v，f[v]应该是f[u]中除去e这条边的概率与g[v]的并集
 * 那么两遍树dp好了。
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, double> edge;
const int maxn = 500001;
const double eps = 1e-8;
int n;
vector<edge> e[maxn];
double q[maxn], f[maxn], g[maxn], ans;
inline bool cmp0(double x) { return -eps < x && x < eps; }
inline double merge(double x, double y) { return x + y - x * y; }
inline double split(double r, double y) { return cmp0(1 - y) ? 1 : (r - y) / (1 - y); }
void dfs1(int u, int fa)
{
	g[u] = q[u];
	for(vector<edge>::iterator it = e[u].begin(), jt = e[u].end(); it != jt; ++it)
		if(it -> first != fa)
		{
			dfs1(it -> first, u);
			g[u] = merge(g[u], g[it -> first] * it -> second);
		}
}
void dfs2(int u, int fa)
{
	ans += f[u];
	for(vector<edge>::iterator it = e[u].begin(), jt = e[u].end(); it != jt; ++it)
		if(it -> first != fa)
		{
			f[it -> first] = merge(g[it -> first], split(f[u], g[it -> first] * it -> second) * it -> second);
			dfs2(it -> first, u);
		}
}
int main()
{
	int u, v;
	double w;
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		scanf("%d%d%lf", &u, &v, &w);
		w /= 100.0;
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	for(int i = 1; i <= n; ++i)
	{
		scanf("%lf", q + i);
		q[i] /= 100.0;
	}
	dfs1(1, 0);
	f[1] = g[1];
	dfs2(1, 0);
	printf("%.6f\n", ans);
	return 0;
}
