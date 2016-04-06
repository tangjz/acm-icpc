#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50010;
int n, a, b, w[maxn], id[maxn], ans;
bool s[maxn];
bool cmp(const int &x, const int &y)
{
	return w[x] < w[y];
}
int main()
{
	int l, r, m;
	char op[5];
	freopen("learning.in", "r", stdin);
	freopen("learning.out", "w", stdout);
	scanf("%d%d%d", &n, &a, &b);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s%d", op, w + i);
		s[i] = op[0] == 'S';
		id[i] = i;
	}
	sort(id, id + n, cmp);
	l = a, r = min(w[id[0]] - 1, b);
	if(l <= r)
		ans += r - l + 1;
	for(int i = 1; i < n; ++i)
	{
		if(s[id[i - 1]])
			l = w[id[i - 1]];
		else
			l = w[id[i - 1]] + w[id[i]] + 1 >> 1;
		if(s[id[i]])
			r = w[id[i]] - 1;
		else
			r = w[id[i - 1]] + w[id[i]] >> 1;
		if(!s[id[i - 1]] && !s[id[i]])
			continue;
		l = max(l, a);
		r = min(r, b);
		if(l <= r)
			ans += r - l + 1;
	}
	l = max(a, w[id[n - 1]]), r = b;
	if(l <= r)
		ans += r - l + 1;
	printf("%d\n", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
