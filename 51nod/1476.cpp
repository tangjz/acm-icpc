#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50002;
char s[maxn];
int val[maxn][2], sum;
long long ans;
priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > Q;
int main()
{
	scanf("%s", s);
	for(int i = 0; s[i]; ++i)
		if(s[i] == '?')
			scanf("%d%d",&val[i][0], &val[i][1]);
	for(int i = 0; s[i]; ++i)
	{
		if(s[i] == '(')
			++sum;
		else if(s[i] == ')')
			--sum;
		else
		{
			s[i] = ')';
			--sum;
			Q.push(make_pair(val[i][0] - val[i][1], i));
			ans += val[i][1];
		}
		if(sum < 0)
		{
			if(Q.empty())
			{
				ans = -1;
				break;
			}
			pair<int, int> tmp = Q.top();
			Q.pop();
			ans += tmp.first;
			s[tmp.second] = '(';
			sum += 2;
		}
	}
	if(sum)
		ans = -1;
	printf("%lld\n", ans);
	return 0;
}
