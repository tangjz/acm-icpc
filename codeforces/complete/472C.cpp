#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n;
struct Name
{
	string name;
	int no;
	bool operator < (const Name &t) const { return name < t.name; }
} person[233333];
int no[233333], f[233333], g[233333], ans;
char str[100];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", str);
		person[i << 1].name = str;
		person[i << 1].no = i;
		scanf("%s", str);
		person[(i << 1) + 1].name = str;
		person[(i << 1) + 1].no = i;
	}
	sort(person, person + n * 2);
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		no[x - 1] = i;
	}
	n <<= 1;
	memset(g, 0x3f, sizeof(g));
	for(int i = 0, x; i < n; ++i)
	{
		f[i] = no[person[i].no];
		x = lower_bound(g + 1, g + n + 1, f[i]) - g;
		g[x] = f[i];
		ans = max(ans, x);
	}
	if(ans >= (n >> 1)) printf("YES\n");
	else printf("NO\n");
	return 0;
}
