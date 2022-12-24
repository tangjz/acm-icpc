#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
template<class T> void scan(T &x)
{
    int ch;
    while((ch = getchar()) < '0' || ch > '9');
    x = ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch - '0');
}
template<class T> void print(T x)
{
    int len = 0, num[20];
    while(x)
    {
        num[len++] = x % 10;
        x /= 10;
    }
    if(!len)
        num[len++] = 0;
    while(len)
        putchar('0' + num[--len]);
    putchar('\n');
}
typedef long long LL;
const int maxk = 64 + 1, maxs = 18, maxm = 69996;
const LL maxn = (LL)1e18 + 1;
LL c[maxk][maxm];
vector<LL> ans[maxk];
int main()
{
	for(int m = 0; m < maxm; ++m)
	{
		c[0][m] = 1;
		ans[0].push_back(0);
	}
	for(int k = 1; k < maxk; ++k)
		for(int m = 0; m < maxm; ++m)
		{
			c[k][m] = k <= m ? c[k][m - 1] + c[k - 1][m - 1] : 0;
			LL val = ans[k - 1][m] + c[k][m];
			if(val >= maxn)
			{
				ans[k].push_back(maxn);
				break;
			}
			ans[k].push_back(val);
		}
	LL k, n;
	while(scan(k), scan(n), k && n)
	{
		if(k == 1)
			print(n);
		else if(k == 2)
		{
			LL ans = (LL)ceil((sqrt(n * 8 + 1.0) - 1) * 0.5);
			while(ans * (ans + 1) / 2 >= n)
				--ans;
			while(ans * (ans + 1) / 2 < n)
				++ans;
			print(ans);
		}
		else if(k == 3)
		{
			LL ans = (LL)ceil(pow(n * 6, 1.0 / 3) + 0.5);
			while(ans * (ans * ans + 5) / 6 >= n)
				--ans;
			while(ans * (ans * ans + 5) / 6 < n)
				++ans;
			print(ans);
		}
		else
		{
			if(k >= maxk)
				k = maxk - 1;
			print(lower_bound(ans[k].begin(), ans[k].end(), n) - ans[k].begin());
		}
	}
	return 0;
}