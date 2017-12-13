#include <bitset>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100000, maxm = 5000, maxd = 26;
int t, n, m;
bitset<maxn + 1> pos[maxd + 1], f[3];
char str[maxn + 3], pat[maxm + 3];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%s%s", &n, &m, str + 1, pat + 1);
		for(int i = 0; i < maxd; ++i)
			pos[i].reset();
		for(int i = 1; i <= n; ++i) {
			int ch = str[i] - 'a';
			pos[ch].set(i);
		}
		pat[0] = pat[m + 1] = 'a' + maxd;
		f[0].set();
		f[1].reset();
		int cur = 1, nxt = 2;
		for(int i = 1; i <= m; ++i, swap(cur, nxt)) {
			f[nxt] = (f[0] << 1) & pos[pat[i + 1] - 'a'];
			f[0] = ((f[0] << 1) & pos[pat[i] - 'a']) | ((f[cur] << 1) & pos[pat[i - 1] - 'a']);
		}
		f[0] |= f[cur];
		for(int i = 1; i <= n; ++i)
			str[i] = '0' + (i + m - 1 <= n && f[0].test(i + m - 1));
		puts(str + 1);
	}
	return 0;
}
