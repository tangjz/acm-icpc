#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
typedef priority_queue<edge, vector<edge>, greater<edge> > MinQueue;
const int INF = 0x3f3f3f3f, NIL = -1;
int n;
char g[1001] = {};
int main()
{
	int l, r = 0;
	scanf("%d\n%s", &n, g);
	while(g[r] == '.' && r < n) ++r;
	l = r;
	while(g[l] == g[r] && r < n) ++r;
	if(g[r] == '.' || r >= n)
	{
		if(g[l] == 'R') printf("%d %d\n", l + 1, r + 1);
		else if(g[l] == 'L') printf("%d %d\n", r, l);
		else printf("1 1\n");
	}
	else printf("%d %d\n", l + 1, r);
	return 0;
}
