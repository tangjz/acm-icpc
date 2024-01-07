#include <cstdio>
const long double ans = 0.292762519060695649518959120713854688849038583906493915331;
int main()
{
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		double ret = ans * n * n;
		printf("%.2f\n", ret);
	}
	return 0;
}
