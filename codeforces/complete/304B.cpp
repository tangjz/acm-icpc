#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>

using namespace std;
const int day_tab[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
int sta[3], end[3], cnt;

bool check()
{
	if(sta[0] > end[0]) return true;
	if(sta[0] < end[0]) return false;
	if(sta[1] > end[1]) return true;
	if(sta[1] < end[1]) return false;
	if(sta[2] > end[2]) return true;
	return false;
}
bool runnian(int year) { if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0) return true; return false; }
int count(int year, int month, int day, int flag)
{
	int p = runnian(year), i, s;
	if(flag)
	{
		s = day;
		for(i = 1; i < month; ++i) s += day_tab[p][i - 1];
	}
	else
	{
		s = day_tab[p][month - 1] - day;
		for(i = month + 1; i <= 12; ++i) s += day_tab[p][i - 1];
	}
	return s;
}
int main()
{
	int i;
	scanf("%d:%d:%d", &sta[0], &sta[1], &sta[2]);
	scanf("%d:%d:%d", &end[0], &end[1], &end[2]);
	if(check()) swap(sta[0], end[0]), swap(sta[1], end[1]), swap(sta[2], end[2]);
	if(sta[0] < end[0])
	{
		cnt = count(sta[0], sta[1], sta[2], 0);
		for(i = sta[0] + 1; i < end[0]; ++i)
			if(runnian(i)) cnt += 366;
			else cnt += 365;
		cnt += count(end[0], end[1], end[2], 1);
	}
	else if(sta[0] == end[0]) cnt = count(end[0], end[1], end[2], 1) - count(sta[0], sta[1], sta[2], 1);
	printf("%d\n", cnt);
	return 0;
}
