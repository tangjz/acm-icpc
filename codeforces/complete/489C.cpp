#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int m, s, str1[233], str2[233], cnt1, cnt2;
int main()
{
	scanf("%d%d", &m, &s);
	if(s == 0)
	{
		if(m == 1)
			puts("0 0");
		else
			puts("-1 -1");
		return 0;
	}
	if(s > 9 * m)
	{
		puts("-1 -1");
		return 0;
	}
	str1[m - 1] = str2[m - 1] = cnt1 = cnt2 = 1;
	for(int i = 0; i < m && cnt1 < s; ++i)
		if(cnt1 + 9 - str1[i] < s)
		{
			cnt1 += 9 - str1[i];
			str1[i] = 9;
		}
		else
		{
			str1[i] += s - cnt1;
			cnt1 = s;
		}
	for(int i = m - 1; i >= 0 && cnt2 < s; --i)
		if(cnt2 + 9 - str2[i] < s)
		{
			cnt2 += 9 - str2[i];
			str2[i] = 9;
		}
		else
		{
			str2[i] += s - cnt2;
			cnt2 = s;
		}
	for(int i = m - 1; i >= 0; --i)
		putchar('0' + str1[i]);
	putchar(' ');
	for(int i = m - 1; i >= 0; --i)
		putchar('0' + str2[i]);
	putchar('\n');
	return 0;
}
