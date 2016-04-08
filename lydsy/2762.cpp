/*
 * 区间修改 单点询问 注意方程的解 (吐魂 
 */
#include <cstdio>
const int m = 1 << 21, maxn = 1000000, add = 1000001;
int n, num[100001][2], tot = 0;
bool vis[100001];
struct SegmentTree
{
	int tree[1 << 22];
	void change(int n, const int &val) { for(tree[n += m] += val, n >>= 1; n; n >>= 1) tree[n] = tree[n << 1] + tree[(n << 1) + 1]; }
	int query(int t)
	{
		int s = 1, ans = 0;
		for(s += m - 1, t += m + 1; s ^ t ^ 1; s >>= 1, t >>= 1)
		{
			if(~s & 1) ans += tree[s ^ 1];
			if(t & 1) ans += tree[t ^ 1];
		}
		return ans;
	}
} Tree;
void check(int l, int r)
{
	if(l > maxn || r < -maxn || l > r) return;
	if(l < -maxn) num[tot][0] = -maxn;
	else num[tot][0] = l;
	if(r > maxn) num[tot][1] = maxn;
	else num[tot][1] = r;
	Tree.change(num[tot][0] + add, 1);
	if(num[tot][1] < maxn) Tree.change(num[tot][1] + 1 + add, -1);
	vis[tot] = true;
}
int main()
{
	int x, y, z, tmp;
	char ch[10];
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", ch);
		if(ch[0] == 'A')
		{
			scanf("%d%d%d", &x, &y, &z);
			++tot;
			y = z - y;
			if(!x) { if(y < 0) check(-maxn, maxn); }
			else if(!y)
			{
				if(x < 0) check(-maxn, -1);
				else check(1, maxn);
			}
			else if(y > 0)
			{
				if(x > 0) check(y / x + 1, maxn);
				else check(-maxn, -(y / (-x) + 1));
			}
			else if(y < 0)
			{
				if(x > 0) check(-((-y - 1) / x), maxn);
				else check(-maxn, (-y - 1) / (-x));
			}
		}
		else if(ch[0] == 'D')
		{
			scanf("%d", &x);
			
			if(!vis[x]) continue;
			Tree.change(num[x][0] + add, -1);
			if(num[x][1] < maxn) Tree.change(num[x][1] + 1 + add, 1);
			vis[x] = false;
		}
		else
		{
			scanf("%d", &x);
			printf("%d\n", Tree.query(x + add));
		}
	}
	return 0;
}

