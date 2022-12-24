#include <cstdio>
#include <algorithm>
using namespace std;
int n, que[2001], t1, t2;
struct Node { int a, b, Min, idx; } work[2001];
bool cmp(const Node &x, const Node &y) { return x.Min < y.Min; }
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%d", &work[i].a), work[i].idx = i + 1;
    for(int i = 0; i < n; ++i) scanf("%d", &work[i].b), work[i].Min = min(work[i].a, work[i].b);
	sort(work, work + n, cmp);
	for(int i = 0, head = 0, tail = n - 1; i < n; ++i)
		if(work[i].Min == work[i].a) que[head++] = i;
		else que[tail--] = i;
	for(int i = 0; i < n; ++i)
	{
		t1 += work[que[i]].a;
		t2 = max(t1, t2) + work[que[i]].b;
	}
	printf("%d\n", t2);
	for(int i = 0; i < n - 1; ++i) printf("%d ", work[que[i]].idx);
	printf("%d\n", work[que[n - 1]].idx);
	return 0;
}