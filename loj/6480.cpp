#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 11;
int n, m, f[maxn], border[maxm][maxn], ord[maxm];
char str[maxm][maxn];
inline bool cmp(int const &x, int const &y) {
	int lim = max(border[x][0], border[y][0]);
	for(int i = 1; i <= lim; ++i)
		if(border[x][i] != border[y][i])
			return border[x][i] < border[y][i];
	return x < y;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0, j, k; i < m; ++i) {
		ord[i] = i;
		char *buf = str[i];
		int *seq = border[i];
		scanf("%s", buf);
		for(j = 1, k = 0; buf[j]; ++j) {
			for( ; k && buf[j] != buf[k]; k = f[k]);
			f[j + 1] = buf[j] == buf[k] ? ++k : 0;
		}
		int len = j;
		for(j = f[j]; j; j = f[j])
			if((len << 1) - j <= n)
				seq[++seq[0]] = j;
	}
	sort(ord, ord + m, cmp);
	for(int i = 0; i < m; ++i)
		printf("%s\n", str[ord[i]]);
	return 0;
}
