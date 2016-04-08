#include <stdio.h>
const int maxn = 50001;
int n, a[maxn], b[maxn], ans;
void merge_sort(int *l, int *r)
{
	if(l >= r)
		return;
	int *m = l + (r - l) / 2;
	merge_sort(l, m);
	merge_sort(m + 1, r);
	int *i = l, *j = m + 1, k = 0;
	while(i <= m && j <= r)
		if(*i <= *j)
			b[k++] = *(i++);
		else
		{
			ans += m - i + 1;
			b[k++] = *(j++);
		}
	while(i <= m)
		b[k++] = *(i++);
	while(j <= r)
		b[k++] = *(j++);
	for(int t = 0; t < k; ++t)
		*(l++) = b[t];
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	merge_sort(a, a + n - 1);
	printf("%d\n", ans);
	return 0;
}
