/*
 * LIS O(NlogN)
 */
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = ~0u >> 1;
int ScanInt(void)
{
	int c, r = 0, f = 0;
	while(!isdigit(c = getchar()) && c != '-');
	if(c == '-') f = 1;
	else r = c - '0';
	while(isdigit(c = getchar())) r = (r << 3) + (r << 1) + c - '0';
	return f ? -r : r;
}
int p, buf[10];
void PrintInt(int x)
{
	if(!x) ++p;
	while(x) buf[p++] = x % 10, x /= 10;
	while(p--) putchar('0' + buf[p]);
}
int n, g[5002], ans;
int main()
{
	int num, len;
	n = ScanInt();
	for(int i = 1; i <= n; ++i) g[i] = INF;
	for(int i = 0; i < n; ++i)
	{
		num = ScanInt();
		len = lower_bound(g + 1, g + n + 1, num) - g;
		g[len] = num;
		if(ans < len) ans = len;
	}
	PrintInt(ans);
	return 0;
}

