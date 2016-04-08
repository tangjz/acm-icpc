#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 500010;
int n, o;
pair<char, int> p[maxn];
char s[maxn], t[maxn];
bool vis[maxn];
int main()
{
	scanf("%d%s", &n, s);
	for(int i = 0; i < n; ++i)
		p[i] = {s[i], i};
	sort(p, p + n);
    for(int i = 0; i < n; ++i)
        if(p[i].first < p[o].first)
            o = i;
	for(int i = 0; i < n; ++i, o = p[o].second)
	{
		if(vis[o])
		{
			puts("No Solution");
			return 0;
		}
		vis[o] = 1;
		t[i] = p[o].first;
	}
    puts(t);
	return 0;
}

