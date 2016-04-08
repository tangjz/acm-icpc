#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 500010;
int n, o;
pair<int, int> p[maxn];
int main()
{
	scanf("%d%*d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &p[i].first);
		p[i].second = i;
	}
	sort(p, p + n);
	for(int i = 0; i < n; ++i)
		if(p[i].first < p[o].first)
			o = i;
	for(int i = 0; i < n; ++i, o = p[o].second)
		printf("%d%c", p[o].first, " \n"[i == n - 1]);
	return 0;
}

