#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 101;
int n, m, b, f, l[maxn], r[maxn];
set<int> p;
int main()
{
	scanf("%d%d%d%d", &m, &b, &f, &n);
	p.insert(-b);
	p.insert(m + f);
	for(int i = 1; i <= n; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(x == 1)
		{
			bool flag = 0;
			for(set<int>::iterator it = p.begin(), jt = ++p.begin(); it != p.end(); it = ++jt, ++jt)
				if(*it + b + y + f <= *jt)
				{
					l[i] = *it + b;
					r[i] = *it + b + y;
					printf("%d\n", l[i]);
					p.insert(l[i]);
					p.insert(r[i]);
					flag = 1;
					break;
				}
			if(!flag)
				puts("-1");
		}
		else
		{
			p.erase(l[y]);
			p.erase(r[y]);
		}
	}
	return 0;
}
