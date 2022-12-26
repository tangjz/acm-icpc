#include <set>
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 10, INF = 0x3f3f3f3f;
//fenwick tree
int bit_n, bit[maxn];
void add(int x, int val)
{
	for( ; x <= bit_n; x += x & -x)
		bit[x] += val;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
//disjoint set union
int fa[maxn], vis[maxn];
long long size[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y, long long delta = 0)// y into x's set
{
	int u = find(x), v = find(y);
	if(u != v)
	{
		fa[v] = u;
		size[u] += size[v] + delta;
		size[v] = 0;
	}
}
//sweep line
struct Line
{
	int id, x, y1, y2, type;
	bool operator < (const Line &t) const
	{
		return x < t.x || x == t.x && type < t.type;
	}
} e[maxn << 1];
int e_tot, pos[maxn << 1];
int y_tot, ypos[maxn << 1];
set<int> Sta, End, y_set;
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		fa[i] = i;
		if(x1 == x2)
		{
			size[i] = y2 - y1;
			e[e_tot++] = (Line){i, x1, y1, y2, 1};
			ypos[y_tot++] = y1;
			ypos[y_tot++] = y2;
		}
		else
		{
			size[i] = x2 - x1;
			e[e_tot++] = (Line){i, x1, y1, 0, 0};
			e[e_tot++] = (Line){i, x2, y1, 0, 2};
			ypos[y_tot++] = y1;
		}
	}
	sort(ypos, ypos + y_tot);
	bit_n = y_tot = unique(ypos, ypos + y_tot) - ypos;
	for(int i = 0; i < e_tot; ++i)
	{
		e[i].y1 = lower_bound(ypos, ypos + y_tot, e[i].y1) - ypos + 1;
		if(e[i].type == 1)
			e[i].y2 = lower_bound(ypos, ypos + y_tot, e[i].y2) - ypos + 1;
	}
	sort(e, e + e_tot);
	Sta.insert(-INF), Sta.insert(INF);//块的上端
	End.insert(-INF), End.insert(INF);//块的下端
	y_set.insert(-INF), y_set.insert(INF);//当前集合里的点
	for(int i = 0; i < e_tot; ++i)
		if(!e[i].type)//添加起点
		{
			int &y1 = e[i].y1;
			y_set.insert(y1);//添加节点
			pos[y1] = e[i].id;//添加归属
			add(y1, 1);
			int yy = *(--Sta.upper_bound(*End.lower_bound(y1)));//在Sta里小于End里>=y1的点y2的点yy，即包含y1的块[yy,y2]的起点yy
			Sta.insert(y1);//插入一个块, [y1, y1]
			End.insert(y1);
			if(yy <= y1)//存在包含它的块，需要分裂成两个[yy, y3], [y4, y2]
			{
				Sta.insert(*y_set.upper_bound(y1));//点集里>y1的点y4 (y4<=y2)
				End.insert(*(--y_set.lower_bound(y1)));//点集里<y1的点y3 (y3>=yy)
			}
		}
		else if(e[i].type == 1)//统计、合并
		{
			int &y1 = e[i].y1, &y2 = e[i].y2;
			if(y_set.lower_bound(y1) == y_set.upper_bound(y2))//孤立的线段, 不用处理, 否则至少有一个块
				continue;
			set<int>::iterator lpos = End.lower_bound(y1), rpos = End.lower_bound(y2);//涉及的块的起点与终点 [..., lpos], ..., [..., rpos]
			if(y2 < *(--Sta.upper_bound(*rpos)))//如果rpos所在块不与线段接触则删除
				--rpos;
			int cnt = 1, u = find(pos[*rpos]), v, tmp, stop = *rpos;//设最后一个块是父亲
			vis[u] = i + 1;//更新时间戳
			for(set<int>::iterator it = lpos; *it != stop; it = End.upper_bound(tmp))//由于删除操作已经删除了it, 迭代器全部失效
			{
				tmp = *it;//缓存数据
				v = find(pos[tmp]);//看该块的根
				if(vis[v] != i + 1)//是否已经更新
				{
					vis[v] = i + 1;
					++cnt;//新块
				}
				merge(u, v);//合并u,v所在块
				End.erase(tmp);//合并该块和下一个块
				Sta.erase(Sta.upper_bound(tmp));//合并[l1, r1], [l2, r2]通过删除r1和l2
			}
			merge(u, e[i].id, cnt - sum(y2) + sum(y1 - 1));//合并竖线，增加答案
		}
		else//删除节点
		{
			int &y1 = e[i].y1;
			y_set.erase(y1);//擦除
			pos[y1] = 0;//擦除归属
			add(y1, -1);//取消贡献
			int lpos = *(--Sta.upper_bound(y1)), rpos = *End.lower_bound(y1);//找到对应的块[lpos, rpos]
			if(lpos != y1 && rpos != y1)//在块内，无需修改块
				continue;
			if(lpos != y1)//新下端点
				End.insert(*(--y_set.lower_bound(y1)));
			if(rpos != y1)//新上端点
				Sta.insert(*y_set.upper_bound(y1));
			if(lpos == y1)//删上端点
				Sta.erase(y1);
			if(rpos == y1)//删下端点
				End.erase(y1);
		}
	long long ans = 0;
	for(int i = 1; i <= n; ++i)
		if(i == find(i) && ans < size[i])
			ans = size[i];
	printf("%I64d\n", ans);
	return 0;
}
