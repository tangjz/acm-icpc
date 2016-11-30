#include <cstdio>
const int maxn = 201, e[5][5] = {
{0, 0, 1, 1, 0},
{1, 0, 0, 1, 0},
{0, 1, 0, 0, 1},
{0, 0, 1, 0, 1},
{1, 1, 0, 0, 0}};
int n, na, nb, a[maxn], b[maxn], ansa, ansb;
int main()
{
	scanf("%d%d%d", &n, &na, &nb);
	for(int i = 0; i < na; ++i)
		scanf("%d", a + i);
	for(int i = 0; i < nb; ++i)
		scanf("%d", b + i);
	for(int i = 0; i < n; ++i)
	{
		ansa += e[a[i % na]][b[i % nb]];
		ansb += e[b[i % nb]][a[i % na]];
	}
	printf("%d %d\n", ansa, ansb);
	return 0;
}
