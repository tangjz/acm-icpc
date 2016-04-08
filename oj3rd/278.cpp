#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000001, mod = 2333333, maxs = 101;
int t, top, n, seq[maxn], m, x, tot, pre[mod], tm[mod];
char ch, str[maxs];
struct Hash
{
	int nxt, val;
} e[maxn];
void insert(int x)
{
	int pos = x % mod;
	if(pos < 0)
		pos += mod;
	if(tm[pos] != t)
	{
		pre[pos] = 0;
		tm[pos] = t;
	}
	for(int it = pre[pos]; it; it = e[it].nxt)
		if(e[it].val == x)
			return;
	e[++tot] = (Hash){pre[pos], x};
	pre[pos] = tot;
}
bool find(int x)
{
	int pos = x % mod;
	if(pos < 0)
		pos += mod;
	if(tm[pos] != t)
	{
		pre[pos] = 0;
		tm[pos] = t;
	}
	for(int it = pre[pos]; it; it = e[it].nxt)
		if(e[it].val == x)
			return 1;
	return 0;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		while((ch = getchar()) != '\n');
		for(n = 0; (ch = getchar()) != '\n'; )
			if(ch == ' ')
			{
				if(!top)
					continue;
				str[top] = '\0';
				sscanf(str, "%d", &x);
				insert(x);
				top = 0;
			}
			else if(ch >= '0' && ch <= '9' || ch == '-')
				str[top++] = ch;
		if(top)
		{
			str[top] = '\0';
			sscanf(str, "%d", &x);
			insert(x);
			top = 0;
		}
		scanf("%d", &m);
		while(m--)
		{
			scanf("%d", &x);
			puts(find(x) ? "Yes." : "No.");
		}
	}
	return 0;
}
