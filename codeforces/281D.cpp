#include <stdio.h>
const int maxn = 100001;
int n, a[maxn], top, s[maxn], ans;
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = 0; i < n; ++i)
	{
		while(top && a[s[top - 1]] <= a[i])
			--top;
		if(top)
			upd(ans, a[s[top - 1]] ^ a[i]);
		s[top++] = i;
	}
	top = 0;
	for(int i = n - 1; i >= 0; --i)
	{
		while(top && a[s[top - 1]] <= a[i])
			--top;
		if(top)
			upd(ans, a[s[top - 1]] ^ a[i]);
		s[top++] = i;
	}
	printf("%d\n", ans);
	return 0;
}
