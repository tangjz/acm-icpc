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
int t, sx, sy, tx, ty;
char ch[100001] = {};
int main()
{
	int i;
	scanf("%d%d%d%d%d\n%s", &t, &sx, &sy, &tx, &ty, ch);
	for(i = 0; i < t; ++i)
	{
		if(ch[i] == 'S' && sy > ty) --sy;
		if(ch[i] == 'E' && sx < tx) ++sx;
		if(ch[i] == 'N' && sy < ty) ++sy;
		if(ch[i] == 'W' && sx > tx) --sx;
		if(sx == tx && sy == ty) break;
	}
	if(i < t) printf("%d\n", i + 1);
	else printf("-1\n");
	return 0;
}
