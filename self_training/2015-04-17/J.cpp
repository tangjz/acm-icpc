#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, p, k, rmx;
struct Node
{
	int a, b, id, rd;
} x[maxn], y[maxn];
bool cmp1(const Node &x, const Node &y)
{
	return x.b < y.b || x.b == y.b && x.a > y.a;
}
bool cmp2(const Node &x, const Node &y)
{
	return x.a > y.a || x.a == y.a && x.b > y.b;
}
int main()
{
	scanf("%d%d%d", &n, &p, &k);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", &x[i].a, &x[i].b);
		x[i].id = i;
	}
	sort(x, x + n, cmp1);
	for(int i = 0; i < n; ++i)
	{
		x[i].rd = i;
		y[i] = x[i];
	}
	sort(x + p - k, x + n, cmp2);
	rmx = n - 1;
	for(int i = p - k; i < p; ++i)
	{
		printf("%d ", x[i].id + 1);
		if(x[i].rd < rmx)
			rmx = x[i].rd;
	}
	for(int i = 1; i <= p - k; ++i)
		printf("%d%c", y[rmx - i].id + 1, " \n"[i == p - k]);
	return 0;
}
