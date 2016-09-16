#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
template<class T> void scan(T& x)
{
	int ch, flag;
	while(!isdigit(ch = getchar()) && ch != '-');
	x = (flag = ch == '-') ? 0 : ch - '0';
	while(isdigit(ch = getchar()))
		x = (x << 3) + (x << 1) + ch - '0';
	if(flag)
		x = -x;
}
const int maxn = 101, maxm = 50001;
int t, n, m, a[maxn], b[maxn], c[maxn], cnt;
pair<LL, LL> h[maxm];
int main()
{
	scan(t);
	while(t--)
	{
		scan(n), scan(m);
		cnt = n + 1;
		for(int i = 0; i < n; ++i)
		{
			scan(a[i]), scan(b[i]), scan(c[i]);
			for(int j = 0; j < i; ++j)
				cnt += a[i] * b[j] != b[i] * a[j];
		}
		for(int i = 0; i < m; ++i)
		{
			int x, y;
			scan(x), scan(y);
			h[i] = {0, 0};
			for(int j = 0; j < n; ++j)
				if((LL)a[j] * x + (LL)b[j] * y + c[j] > 0)
				{
					if(j < 50)
						h[i].first |= 1LL << j;
					else
						h[i].second |= 1LL << j - 50;
				}
		}
		sort(h, h + m);
		cnt -= unique(h, h + m) - h;
		puts(cnt ? "VULNERABLE" : "PROTECTED");
	}
	return 0;
}
