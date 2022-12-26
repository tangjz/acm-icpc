/*
 * 开个栈维护半平面交即可
 */
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const double exp = 0.000000000000001;
struct Line
{
	int a, b, num;
	bool operator == (const Line &x) const { return a == x.a; }
	bool operator < (const Line &x) const { return a < x.a || a == x.a && b > x.b; }
    void read(const int x) { num = x; scanf("%d%d", &a, &b); }
} line[50001], q[50001];
int dcmp(const double x) { if(x > exp) return 0; return 1; }
double Cross(const Line &x, const Line &y) { return (double)(y.b - x.b) / (double)(x.a - y.a); }
int n, out[50001];
int main()
{
	int i, top;
	scanf("%d", &n);
	for(i = 1; i <= n; ++i) line[i].read(i);
	sort(&line[1], &line[n + 1]);
    n = unique(&line[1], &line[n + 1]) - &line[1];
	for(top = i = 1; i <= n; ++i)
	{
		while(top > 2 && Cross(q[top - 1], q[top - 2]) > Cross(q[top - 1], line[i]) - exp) --top;
		q[top++] = line[i];
	}
	for(i = 1; i < top; ++i) out[i] = q[i].num;
	sort(&out[1], &out[top]);
	for(i = 1; i < top; ++i) printf("%d ", out[i]);
	printf("\n");
	return 0;
}
