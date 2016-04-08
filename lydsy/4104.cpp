#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int n, pos;
pair<int, int> p[maxn];
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	scan(n), scan(pos);
	for(int i = 0, x; i <= n; ++i)
	{
		scan(p[i].first);
		p[i].second = i;
		if(!p[i].first)
			pos = i;
	}
	sort(p, p + n + 1);
	for(int i = 1; i <= n; ++i, pos = p[pos].second)
		printf("%d ", p[pos].first);
	putchar('\n');
	return 0;
}
