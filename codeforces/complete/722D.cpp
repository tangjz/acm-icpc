#include <set>
#include <stdio.h>
using namespace std;
const int maxn = 50001;
int n;
set<int> sp;
int main()
{
	scanf("%d", &n);
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		sp.insert(x);
	}
	while(1)
	{
		int v = *sp.rbegin();
		bool flag = 0;
		for( ; v > 1 && !flag; v >>= 1)
			flag |= !sp.count(v >> 1);
		if(!flag)
			break;
		sp.erase(*sp.rbegin());
		sp.insert(v);
	}
	for(set<int>::iterator it = sp.begin(); it != sp.end(); ++it)
		printf("%d ", *it);
	putchar('\n');
	return 0;
}
