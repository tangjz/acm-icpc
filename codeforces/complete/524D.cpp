#include <cstdio>
const int maxn = 20001;
int n, m, t, a[maxn], l, r, que[maxn], ans, out[maxn];
bool flag;
int main()
{
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 0; i < n; ++i)
	{
		int hh, mm, ss;
		scanf("%d:%d:%d", &hh, &mm, &ss);
		a[i] = hh * 3600 + mm * 60 + ss;
		que[r++] = i;
		while(l < r && a[que[r - 1]] - a[que[l]] >= t)
			++l;
		if(r - l == m)
			flag = 1;
		if(r - l <= m)
			out[i] = ++ans;
		else
		{
			out[i] = out[que[r - 2]];
			que[r - 2] = que[r - 1];
			--r;
		}
	}
	if(flag)
	{
		printf("%d\n", ans);
		for(int i = 0; i < n; ++i)
			printf("%d\n", out[i]);
	}
	else
		printf("No solution\n");
	return 0;
}
