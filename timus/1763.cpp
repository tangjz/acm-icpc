#include <set>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int maxn = 9, maxm = 9, maxs = 301, maxp = 111, mod = 1000000009;
struct HashTable {
	int counter, number[maxs];
	unordered_map<int, int> index;
	int pos(int x) { // val == x
		if(index.count(x))
			return index[x];
		number[counter] = x;
		return index[x] = counter++;
	}
	int val(int x) const { // pos == x
		return number[x];
	}
} HT;
int n, m, seq[maxn], low[maxn], upp[maxn], f[2][maxs], cur, pre = 1;
struct Edge {
	int u, v;
} e[maxm];
int min_rep() // seq to num
{
	static int col[maxn];
	int ret = 0;
	for(int j = 1; j <= 7; ++j) // color from [1, 7]
		col[j] = 0;
	for(int j = 0, c = 0; j < 6; ++j)
	{
		if(seq[j])
		{
			if(!col[seq[j]])
				col[seq[j]] = ++c;
			seq[j] = col[seq[j]];
		}
		ret = ret * 7 + seq[j];
	}
	return ret;
}
void num_to_seq(int x) // num to seq, low, upp
{
	for(int j = 1; j < 7; ++j)
		low[j] = upp[j] = -1;
	for(int j = 5; j >= 0; --j)
	{
		seq[j] = x % 7;
		x /= 7;
		if(seq[j])
			low[seq[j]] = j;
	}
	for(int j = 0; j < 6; ++j)
		if(seq[j])
			upp[seq[j]] = j;
}
int trans[maxs][maxs], coeff[maxs];
queue<int> Q;
set<int> sp;
bool g[maxs][maxs], vis[maxs];
void getStatus() // try any possible transform
{
	for(int it = 0; it < HT.counter; ++it)
	{
		int val = HT.val(it);
		sp.insert(val);
		Q.push(val);
	}
	m = 0; // (0, 1, 2, i-4, i-3, i-2) -> (0, 1, 2, i-3, i-2, i-1) : (i-4, i-1), (i-2, i-1)
	e[m++] = (Edge){3, 6};
	e[m++] = (Edge){5, 6};
	while(!Q.empty())
	{
		int cur = Q.front(), cid = HT.pos(cur);
		Q.pop();
		if(!cur) // can not do anything after building a circle
			continue;
		for(int i = 0; i < 1 << m; ++i)
		{
			num_to_seq(cur);
			seq[6] = 7;
			low[7] = upp[7] = 6;
			bool flag = 1;
			for(int j = 0; j < m && flag; ++j)
			{
				if(~i & (1 << j))
					continue;
				int u = e[j].u, v = e[j].v;
				flag &= seq[u] && seq[v];
				if(!flag)
					continue;
				if(seq[u] == seq[v])
				{
					seq[u] = seq[v] = 0;
					for(int k = 0; k < 7; ++k)
						flag &= k == u || k == v || !seq[k];
					continue;
				}
				if(seq[u] > seq[v])
					swap(u, v);
				int col = seq[u];
				int x = low[seq[u]] != u ? low[seq[u]] : upp[seq[u]];
				int y = low[seq[v]] != v ? low[seq[v]] : upp[seq[v]];
				if(x > y)
					swap(x, y);
				seq[u] = seq[v] = 0;
				seq[x] = seq[y] = col;
				low[col] = x;
				upp[col] = y;
			}
			flag &= !seq[3];
			if(!flag)
				continue;
			for(int j = 3; j < 6; ++j)
				seq[j] = seq[j + 1];
			int nxt = min_rep(), nid = HT.pos(nxt);
			++trans[cid][nid];
			g[cid][nid] = 1;
			if(!sp.count(nxt))
			{
				sp.insert(nxt);
				Q.push(nxt);
			}
		}
	}
	//printf("HT size : %d\n", HT.counter);
}
inline void mod_inc(int &x, int y)
{
	(x += y) >= mod && (x -= mod);
}
int tot, ord[maxp];
struct Matrix {
	int r, c, num[maxp][maxp];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j) if(num[i][j])
				for(int k = 0; k < t.c; ++k) if(t.num[j][k])
					ret.num[i][k] = (ret.num[i][k] + (LL)num[i][j] * t.num[j][k]) % mod;
		return ret;
	}
	Matrix pow(int k) const {
		Matrix ret = {r, r}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} A, B, C;
int main()
{
	scanf("%d", &n);
	// start point
	m = 0;
	e[m++] = (Edge){0, 1};
	e[m++] = (Edge){1, 2};
	e[m++] = (Edge){2, 3};
	e[m++] = (Edge){3, 4};
	e[m++] = (Edge){4, 5};
	e[m++] = (Edge){0, 3};
	e[m++] = (Edge){1, 4};
	e[m++] = (Edge){2, 5};
	for(int i = 0; i < 1 << m; ++i)
	{
		for(int j = 0; j < 6; ++j)
		{
			seq[j] = j + 1;
			low[j + 1] = upp[j + 1] = j;
		}
		bool flag = 1;
		for(int j = 0; j < m && flag; ++j)
		{
			if(~i & (1 << j))
				continue;
			int u = e[j].u, v = e[j].v;
			flag &= seq[u] && seq[v];
			if(!flag)
				continue;
			if(seq[u] == seq[v]) // u-v with u-v
			{
				seq[u] = seq[v] = 0;
				for(int k = 0; k < 6; ++k) // must only one circle
					flag &= k == u || k == v || !seq[k];
				continue;
			}
			if(seq[u] > seq[v])
				swap(u, v);
			int col = seq[u]; // x-u with v-y
			int x = low[seq[u]] != u ? low[seq[u]] : upp[seq[u]];
			int y = low[seq[v]] != v ? low[seq[v]] : upp[seq[v]];
			if(x > y)
				swap(x, y);
			seq[u] = seq[v] = 0;
			seq[x] = seq[y] = col;
			low[col] = x;
			upp[col] = y;
		}
		if(!flag)
			continue;
		int hh = min_rep(), id = HT.pos(hh);
		mod_inc(f[cur][id], 1);
	}
	// middle transform
	getStatus();
	for(int k = 0; k < HT.counter; ++k)
		for(int i = 0; i < HT.counter; ++i)
			for(int j = 0; j < HT.counter; ++j)
				g[i][j] = g[i][j] || (g[i][k] && g[k][j]);
	// end point
	m = 0;
	if(n > 6)
	{
		e[m++] = (Edge){3, 0};
		e[m++] = (Edge){4, 1};
		e[m++] = (Edge){5, 2};
	}
	e[m++] = (Edge){5, 0};
	for(int it = 0; it < HT.counter; ++it)
	{
		int cur = HT.val(it);
		for(int i = 0; i < 1 << m; ++i)
		{
			num_to_seq(cur);
			bool flag = 1;
			for(int j = 0; j < m && flag; ++j)
			{
				if(~i & (1 << j))
					continue;
				int u = e[j].u, v = e[j].v;
				flag &= seq[u] && seq[v];
				if(!flag)
					continue;
				if(seq[u] == seq[v])
				{
					seq[u] = seq[v] = 0;
					for(int k = 0; k < 6; ++k)
						flag &= k == u || k == v || !seq[k];
					continue;
				}
				if(seq[u] > seq[v])
					swap(u, v);
				int col = seq[u];
				int x = low[seq[u]] != u ? low[seq[u]] : upp[seq[u]];
				int y = low[seq[v]] != v ? low[seq[v]] : upp[seq[v]];
				if(x > y)
					swap(x, y);
				seq[u] = seq[v] = 0;
				seq[x] = seq[y] = col;
				low[col] = x;
				upp[col] = y;
			}
			for(int j = 0; j < 6 && flag; ++j)
				flag &= !seq[j];
			if(!flag)
				continue;
			++coeff[it];
			vis[it] = 1;
		}
	}
	for(int i = 0; i < HT.counter; ++i)
	{
		for(int j = 0; j < HT.counter; ++j)
			vis[i] = vis[i] || (g[i][j] && vis[j]);
		if(vis[i])
			ord[tot++] = i;
	}
	// matrix
	A.r = C.c = 1;
	A.c = B.r = B.c = C.r = tot;
	for(int i = 0; i < tot; ++i)
	{
		A.num[0][i] = f[cur][ord[i]];
		for(int j = 0; j < tot; ++j)
			B.num[i][j] = trans[ord[i]][ord[j]];
		C.num[i][0] = coeff[ord[i]];
	}
	A = A * B.pow(n - 6) * C;
	mod_inc(A.num[0][0], A.num[0][0]);
	printf("%d\n", A.num[0][0]);
	return 0;
}
