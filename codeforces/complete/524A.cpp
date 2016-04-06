#include <map>
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, k;
set<int> peo;
map<int, set<int> > fri;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		peo.insert(u);
		peo.insert(v);
		fri[u].insert(v);
		fri[v].insert(u);
	}
	set<int> ans;
	for(set<int>::iterator it = peo.begin(); it != peo.end(); ++it)
	{
		for(set<int>::iterator jt = peo.begin(); jt != peo.end(); ++jt)
		{
			if(it == jt || fri[*it].count(*jt))
				continue;
			int cnt = 0;
			set<int> &t = fri[*jt];
			for(set<int>::iterator lt = t.begin(); lt != t.end(); ++lt)
				if(fri[*it].count(*lt))
					++cnt;
			if(cnt * 100 >= fri[*it].size() * k)
				ans.insert(*jt);
		}
		printf("%d: %d", *it, ans.size());
		for(set<int>::iterator jt = ans.begin(); jt != ans.end(); ++jt)
			printf(" %d", *jt);
		putchar('\n');
		ans.clear();
	}
	return 0;
}
