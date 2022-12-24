#include <map>
#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define x first
#define y second
typedef long long LL;
const int maxn = 100001;
int n, sz, m, fir[maxn], ord[maxn], idx[maxn], pos[maxn];
pair<int, int> a[maxn];
map<pair<int, int>, int> Hash;
bool vis[maxn];
LL ans;
bool cmp(const int &u, const int &v)
{
	return a[u].y < a[v].y;
}
namespace fastIO {
	#define BUF_SIZE 100000
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		for(x = ch == '-' ? '0' - nc() : ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	#undef BUF_SIZE
};
using namespace fastIO;
int main()
{
	while(read(n), !IOerror)
	{
		sz = (int)ceil(sqrt(n * 0.1));
		m = 0;
		map<pair<int, int>, int>().swap(Hash);
		ans = 0;
		memset(vis, 0, n * sizeof(bool));
		for(int i = 0; i < n; ++i)
		{
			read(a[i].x), read(a[i].y);
			ord[i] = i;
		}
		a[n].x = a[n].y = ~0u >> 1;
		sort(a, a + n);
		sort(ord, ord + n, cmp);
		for(int i = 0; i < n; ++i)
		{
			if(!i || a[i - 1].x != a[i].x)
				fir[m++] = i;
			pos[i] = m - 1;
		}
		for(int i = 0; i < n; ++i)
			idx[i] = pos[ord[i]];
		fir[m] = n;
		for(int i = 0; i < m; ++i)
		{
			int L = fir[i], R = fir[i + 1];
			if(R - L <= sz)
			{
				for(int j = L; j < R; ++j)
					for(int k = j + 1; k < R; ++k)
						ans += Hash[make_pair(a[j].y, a[k].y)]++;
				continue;
			}
			for(int j = L; j < R; ++j)
				vis[j] = 1;
			memset(pos, 0, m * sizeof(int));
			for(int j = 0, k = L; j < n && k < R; ++j)
			{
				for( ; k < R && a[k].y < a[ord[j]].y; ++k);
				if(!vis[ord[j]] && a[ord[j]].y == a[k].y)
					ans += pos[idx[j]]++;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}