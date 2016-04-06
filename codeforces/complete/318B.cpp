#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std;
string ch;
int start[1000001], end[1000001], cnt1 = 0, cnt2 = 0;
long long ans = 0;
int main()
{
	cin >> ch;
	for(string::size_type it = 0; it < ch.size(); ++it)
	{
		if((it = ch.find("heavy", it)) != string::npos) start[cnt1++] = (int) it + 1;
		else break;
	}
	for(string::size_type it = 0; it < ch.size(); ++it)
	{
		if((it = ch.find("metal", it)) != string::npos) end[cnt2++] = (int) it + 1;
		else break;
	}
	int i = 0, j = 0;
	while(i < cnt1 && j < cnt2)
	{
		while(start[i] <= end[j] && i < cnt1) ++i; --i;
		ans += i + 1;
		++j;
	}
	printf("%I64d\n", ans);
	return 0;
}
