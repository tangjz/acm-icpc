#include <cstdio>
#include <algorithm>
using namespace std;
struct Pair
{
	int val, id;
	Pair(int val = 0, int id = 0) : val(val), id(id) {}
	bool operator < (const Pair &x) const { return val > x.val; }
};
struct Node
{
	int size, tot;
	Pair a[100001];
	void Sort() { sort(a, a + size); }
} boat[2];
int n, v, sum[2];
long long tmp, ans;
int main()
{
	scanf("%d%d", &n, &v);
	for(int i = 1, t, p; i <= n; ++i)
	{
		scanf("%d%d", &t, &p), --t;
		boat[t].a[boat[t].size++] = Pair(p, i);
	}
	boat[0].Sort(), boat[1].Sort();
	while(boat[0].tot < boat[0].size && boat[0].tot < v) tmp += boat[0].a[boat[0].tot++].val;
	while(boat[0].tot >= 0)
	{
		while(boat[1].tot < boat[1].size && boat[0].tot + 2 * (boat[1].tot + 1) <= v)
			tmp += boat[1].a[boat[1].tot++].val;
		if(tmp > ans)
		{
			ans = tmp;
			sum[0] = boat[0].tot;
			sum[1] = boat[1].tot;
		}
		tmp -= boat[0].a[--boat[0].tot].val;
	}
	printf("%I64d\n", ans);
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < sum[i]; ++j) printf("%d ", boat[i].a[j].id);
	printf("\n");
	return 0;
}
