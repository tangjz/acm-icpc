#include <cstdio>
int n, a[1001], b[1001], ans;
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
	while(scanf("%d", &n) == 1)
	{
		ans = 0;
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		merge_sort(a, a + n - 1);
		for(int i = n - 1; i >= 0; --i)
			printf("%d ", a[i]);
		printf("\n%d\n", n * (n - 1) / 2 - ans);
	}
	return 0;
}
