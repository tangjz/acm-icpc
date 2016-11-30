#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 16384;
typedef map<int, int> Order;
typedef pair<int, Order> Orders;
map<int, Orders, greater<int> > Buy;
map<int, Orders, less<int> > Sell;
int n, id, p, q, P[maxn];
template<class A, class B> void Maintain(map<int, Orders, A> &act, map<int, Orders, B> &pass)
{
	while(q > 0)
	{
		if(pass.empty())
			break;
		map<int, Orders, less<int> >::iterator it = pass.begin();
		int pp = it -> first;
		B cmp;
		if(cmp(p, pp))
			break;
		Orders &tmp = it -> second;
		Order::iterator jt = tmp.second.begin();
		int qq = min(q, jt -> second);
		printf("TRADE %d %d\n", qq, pp);
		q -= qq;
		jt -> second -= qq;
		tmp.first -= qq;
		if(!jt -> second)
			tmp.second.erase(jt -> first);
		if(!tmp.first)
			pass.erase(it -> first);
	}
	if(q > 0)
		if(act.find(p) != act.end())
		{
			Orders &tmp = act[p];
			tmp.first += q;
			tmp.second[id] = q;
		}
		else
		{
			Order tmp;
			tmp.clear();
			tmp[id] = q;
			act[p] = make_pair(q, tmp);
		}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		char op[10];
		scanf("%s", op);
		if(op[0] == 'B' || op[0] == 'S')
		{
			scanf("%d%d", &q, &p);
			P[i] = p;
			id = i;
			if(op[0] == 'B')
				Maintain(Buy, Sell);
			else
				Maintain(Sell, Buy);
		}
		else
		{
			scanf("%d", &id);
			if(Buy.find(P[id]) != Buy.end())
			{
				Orders &tmp = Buy[P[id]];
				if(tmp.second.find(id) != tmp.second.end())
				{
					tmp.first -= tmp.second[id];
					tmp.second.erase(id);
				}
				if(!tmp.first)
					Buy.erase(P[id]);
			}
			if(Sell.find(P[id]) != Sell.end())
			{
				Orders &tmp = Sell[P[id]];
				if(tmp.second.find(id) != tmp.second.end())
				{
					tmp.first -= tmp.second[id];
					tmp.second.erase(id);
				}
				if(!tmp.first)
					Sell.erase(P[id]);
			}
		}
		int bq = 0, bp = 0, sq = 0, sp = 99999;
		if(!Buy.empty())
		{
			map<int, Orders, greater<int> >::iterator it = Buy.begin();
			bq = it -> second.first;
			bp = it -> first;
		}
		if(!Sell.empty())
		{
			map<int, Orders, less<int> >::iterator it = Sell.begin();
			sq = it -> second.first;
			sp = it -> first;
		}
		printf("QUOTE %d %d - %d %d\n", bq, bp, sq, sp);
	}
	return 0;
}
