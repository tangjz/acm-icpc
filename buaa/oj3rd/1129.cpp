#include <cstdio>
#include <algorithm>
using namespace std;
int n;
struct Node
{
	int id;
	long long a, b;
	bool operator < (const Node &x) const
	{
		return a * x.b > x.a * b;
	}
} s[1001];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", &s[i].a), s[i].id = i;
		for(int i = 0; i < n; ++i)
			scanf("%d", &s[i].b);
		sort(s, s + n);
		printf("%d\n", s[1].id + 1);
	}
	return 0;
}
