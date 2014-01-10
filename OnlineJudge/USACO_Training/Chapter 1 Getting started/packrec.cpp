/*
ID: tangjin2
LANG: C++
TASK: packrec
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct node { int wide, high; } rp[4], tmp;
int ans;
bool used[101];
node turn(node &x) { tmp.wide = x.high; tmp.high = x.wide; return tmp; }
void copy()
{
	if(tmp.wide * tmp.high < ans || !ans)
	{
		ans = tmp.wide * tmp.high;
		memset(used, 0, sizeof used);
	}
	if(tmp.wide * tmp.high == ans) used[min(tmp.wide, tmp.high)] = 1;
}
void work()
{
	int i;
	tmp.wide = tmp.high = 0;
	for(i = 0; i < 4; ++i)
	{
		tmp.wide += rp[i].wide;
		if(rp[i].high > tmp.high) tmp.high = rp[i].high;
	}
	copy();
	tmp.wide = tmp.high = 0;
	for(i = 0; i < 3; ++i)
	{
		tmp.wide += rp[i].wide;
		if(rp[i].high > tmp.high) tmp.high = rp[i].high;
	}
	tmp.high += rp[3].high;
	if(rp[3].wide > tmp.wide) tmp.wide = rp[3].wide;
	copy();
	tmp.wide = rp[0].wide + rp[1].wide;
	tmp.high = max(rp[0].high, rp[1].high);
	tmp.high += rp[2].high;
	if(rp[2].wide > tmp.wide) tmp.wide = rp[2].wide;
	tmp.wide += rp[3].wide;
	if(rp[3].high > tmp.high) tmp.high = rp[3].high;
	copy();
	tmp.wide = rp[0].wide + rp[1].wide;
	tmp.high = max(rp[0].high, rp[1].high);
	tmp.wide += max(rp[2].wide, rp[3].wide);
	if(rp[2].high + rp[3].high > tmp.high) tmp.high = rp[2].high + rp[3].high;
	copy();
	tmp.high = max(rp[0].high + rp[2].high, rp[1].high + rp[3].high);
	tmp.wide = rp[0].wide + rp[1].wide;
	if(rp[0].high < rp[1].high)
		if(rp[1].wide + rp[2].wide > tmp.wide) tmp.wide = rp[1].wide + rp[2].wide;
	if(rp[0].high + rp[2].high > rp[1].high)
		if(rp[2].wide + rp[3].wide > tmp.wide) tmp.wide = rp[2].wide + rp[3].wide;
	if(rp[1].high < rp[0].high)
		if(rp[0].wide + rp[3].wide > tmp.wide) tmp.wide = rp[0].wide + rp[3].wide;
	if(rp[2].wide > tmp.wide) tmp.wide = rp[2].wide;
	if(rp[3].wide > tmp.wide) tmp.wide = rp[3].wide;
	copy();
}
void transfrom(int dep)
{
	if(dep == 4)
	{
		work();
		return;
	}
	transfrom(dep + 1);
	rp[dep] = turn(rp[dep]);
	transfrom(dep + 1);
	rp[dep] = turn(rp[dep]);
}
void dfs(int dep)
{
	if(dep == 4) transfrom(0);
	for(int i = dep; i < 4; ++i)
	{
		tmp = rp[dep], rp[dep] = rp[i], rp[i] = tmp;
		dfs(dep + 1);
		tmp = rp[dep], rp[dep] = rp[i], rp[i] = tmp;
	}
}
int main()
{
	freopen("packrec.in", "r", stdin);
	freopen("packrec.out", "w", stdout);
	int i;
	for(i = 0; i < 4; ++i) scanf("%d%d", &rp[i].wide, &rp[i].high);
	dfs(0);
	printf("%d\n", ans);
	for(i = 1; i <= 100 ; ++i) if(used[i]) printf("%d %d\n", i, ans / i);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
