#include <set>
#include <map>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 100010, mod = 1000000007;
int n, m, cnt1, cnt2, now;
char s[maxn], t[maxn], q[maxn];
int main()
{
	scanf("%d%d%s%s", &n, &m, s, t);
	for(int i = 0; i < n; ++i)
		if(s[i] == t[i])
			q[i] = s[i];
		else if(now)
		{
			q[i] = s[i];
			now ^= 1;
			++cnt2;
		}
		else
		{
			q[i] = t[i];
			now ^= 1;
			++cnt1;
		}
	if(m < max(cnt1, cnt2))
	{
		puts("-1");
		return 0;
	}
	for(int i = 0; i < n && max(cnt1, cnt2) < m; ++i)
		if(s[i] == t[i])
		{
			for(int j = 'a'; j <= 'z'; ++j)
				if(j != s[i] && j != t[i])
				{
					q[i] = j;
					break;
				}
			++cnt1;
			++cnt2;
		}
	for(int i = 0; i < n && cnt1 < m; ++i)
		if(s[i] != t[i] && s[i] == q[i])
		{
			for(int j = 'a'; j <= 'z'; ++j)
				if(j != s[i] && j != t[i])
				{
					q[i] = j;
					break;
				}
			++cnt1;
		}
	for(int i = 0; i < n && cnt2 < m; ++i)
		if(s[i] != t[i] && t[i] == q[i])
		{
			for(int j = 'a'; j <= 'z'; ++j)
				if(j != s[i] && j != t[i])
				{
					q[i] = j;
					break;
				}
			++cnt2;
		}
	puts(q);
	return 0;
}
