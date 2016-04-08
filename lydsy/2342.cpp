#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 500002;
int t, n, f[maxn], ord[maxn], ans;
set<int> Q;
char s[maxn];
bool cmp(const int &x, const int &y)
{
	return (x - f[x]) < (y - f[y]);
}
int main()
{
	scanf("%d%s", &n, s + 1);
	s[0] = '\r';
	for(int i = 1, mx = 0, id; i <= n; ++i)
	{
		f[i] = mx >= i ? min(mx - i, f[2 * id - i]) : 0;
		while(i + f[i] + 1 <= n && s[i + f[i] + 1] == s[i - f[i]])
			++f[i];
		if(i + f[i] > mx)
		{
			mx = i + f[i];
			id = i;
		}
		ord[i] = i;
	}
	sort(ord + 1, ord + n + 1, cmp);
	for(int i = 1, j = 1; i <= n; ++i)
	{
		for( ; j <= n && ord[j] - f[ord[j]] <= i; ++j)
			Q.insert(ord[j]);
		set<int>::iterator it = Q.upper_bound(i + f[i] / 2);
		if(it != Q.begin())
			ans = max(ans, (*(--it) - i) * 4);
	}
	printf("%d\n", ans);
	return 0;
}
