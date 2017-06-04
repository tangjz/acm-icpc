#include <stdio.h>
const int maxn = 100001;
int n;
struct Node {
	int c[3];
	bool operator == (Node const &t) const {
		return c[0] == t.c[0] && c[1] == t.c[1] && c[2] == t.c[2];
	}
	bool operator < (Node const &t) const {
		if(c[0] != t.c[0])
			return c[0] < t.c[0];
		if(c[1] != t.c[1])
			return c[1] < t.c[1];
		return c[2] < t.c[2];
	}
} a[maxn], b;
int main()
{
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		a[i] = a[i - 1];
		++a[i].c[x];
	}
	b = (Node){a[n].c[0] >> 1, a[n].c[1] >> 1, a[n].c[2] >> 1};
	if(a[n >> 1] == b)
	{
		puts("1");
		return 0;
	}
	for(int i = 1, j = 0; i <= n; ++i)
	{
		Node t = (Node){a[i].c[0] - b.c[0], a[i].c[1] - b.c[1], a[i].c[2] - b.c[2]};
		for( ; j < i && a[j] < t; ++j);
		if(a[j] == t)
		{
			puts("2");
			return 0;
		}
	}
	puts("3");
	return 0;
}
