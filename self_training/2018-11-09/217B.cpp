#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 17, maxp = 8;
const char *seq = "msc", *pat[maxp] = {"022012", "020212", "002212", "012022", "020122", "002122", "010222", "001222"};
int n, nxt[3][maxn];
char buf[maxn];
int main() {
	scanf("%d%s", &n, buf);
	nxt[0][n] = nxt[1][n] = nxt[2][n] = n;
	for(int i = n - 1; i >= 0; --i)
		for(int j = 0; j < 3; ++j)
			nxt[j][i] = buf[i] == seq[j] ? i : nxt[j][i + 1];
	long long ans = 0;
	for(int i = 0; i < n; ++i) {
		int low = n;
		for(int j = 0; j < maxp; ++j) {
			int pos = i - 1;
			for(int k = 0; pos < n && k < 6; ++k)
				pos = nxt[pat[j][k] - '0'][pos + 1];
			low = min(low, pos);
		}
		ans += n - low;
	}
	printf("%lld\n", ans);
	return 0;
}
