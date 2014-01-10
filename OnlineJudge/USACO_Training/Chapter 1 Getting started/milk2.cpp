/*
ID: tangjin2
LANG: C++
TASK: milk2
*/
#include <cstdio>
#include <algorithm>
using namespace std;
struct Node
{
	int l, r;
	bool operator < (const Node &x) const
	{ return l < x.l || l == x.l && r < x.r; }
} farmer[5001];
int max_work, max_relax, N;
int main()
{
	freopen("milk2.in", "r", stdin);
	freopen("milk2.out", "w", stdout);
	int i, j, temp1, temp2, temp3;
	scanf("%d", &n);
	for(i = 1; i <= n; ++i) scanf("%d%d", &farmer[i].l, &farmer[i].r);
	sort(farmer + 1, farmer + n + 1);
	for(i = 1; i < n; ++i)
		if(farmer[i].l >= 0)
		{
			j = 1;
			while(farmer[i].r >= farmer[i + j].l && i + j <= n)
			{
				if(farmer[i].r < farmer[i + j].r) farmer[i].r = farmer[i + j].r;
				farmer[i + j].l = -1;
				++j;
			}
		}
	temp1 = farmer[1].l;
	for(i = 1; i <= n; ++i)
		if(farmer[i].l >= 0)
		{
			temp2 = farmer[i].l - temp1;
			if(temp2 > max_relax) max_relax = temp2;
			temp3 = farmer[i].r - farmer[i].l;
			if(temp3 > max_work) max_work = temp3;
			temp1 = farmer[i].r;
		}
	printf("%d %d\n", max_work, max_relax);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
